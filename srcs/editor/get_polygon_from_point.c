#include <editor.h>

uint8_t		is_edge_in_polygon(t_polygon *poly, t_edge *edge)
{
	uint32_t i;

	i = 0;
	while (i < poly->nb_points)
	{
		if (poly->edges[i] == edge)
			return (1);
		i++;
	}
	return (0);
}

void		update_poly_tab(t_data *data, enum e_poly_tab *poly_tab, t_edge *edge)
{
	uint32_t i;

	i = 0;
	while (i < data->max_element_id)
	{
		if (poly_tab[i] != OUT && data->elements[i].enabled && data->elements[i].polygon.finished)
		{
			if (is_edge_in_polygon(&data->elements[i].polygon, edge))
				poly_tab[i] = IN;
			else
				poly_tab[i] = OUT;
		}
		i++;
	}
}

t_element	*find_other_elem_with_edge(t_data *data, t_edge *edge, t_element *except)
{
	uint16_t	i;
	uint16_t	j;

	i = 0;
	while (i < data->max_element_id)
	{
		if (&data->elements[i] == except)
		{
			i++;
			continue;
		}
		if (data->elements[i].enabled && data->elements[i].polygon.finished)
		{
			j = 0;
			while (j < data->elements[i].polygon.nb_points)
			{
				if (data->elements[i].polygon.edges[j] == edge)
					return (&data->elements[i]);
				j++;
			}
		}
		i++;
	}
	printf("Error : There should be another element with the edge with id : %lu\n", edge - data->edges);
	exit(1);
	return (NULL);
}

t_edge *find_a_nearby_polygon(t_data *data, int *id, float *dist, t_ivec2 *point)
{
	uint32_t		i;
	float			tmp_dist;
	t_edge			*tmp_edge;
	t_edge			*touched_edge;

	i = 0;
	*dist = -1;
	while (i < data->max_element_id)
	{
		if (data->elements[i].enabled && data->elements[i].polygon.finished)
		{
			tmp_dist = is_in_polygon(point, &(data->elements[i].polygon), &tmp_edge);
			if (tmp_dist != -1 && (tmp_dist < *dist || *dist == -1))
			{
				*dist = tmp_dist;
				*id = i;
				touched_edge = tmp_edge;
			}
		}
		i++;
	}
	return (touched_edge);
}

t_edge		*get_edge_not_common(t_polygon *poly, t_polygon *other_poly)
{
	int	i;
	int j;

	i = 0;
	while (i < poly->nb_points)
	{
		j = 0;
		while (j < other_poly->nb_points)
		{
			if (other_poly->edges[j] == poly->edges[i])
				break ;
			j++;
		}
		if (j == other_poly->nb_points)
			return (poly->edges[i]);
		i++;
	}
	printf("Je ense qu'il y a une serieux probleme quelque part\n");
	return (NULL);
}

t_edge		*find_next_edge(t_data *data, enum e_poly_tab *poly_tab, uint16_t *edge_id)
{
	uint32_t i;

	while (*edge_id < data->max_edge_id)
	{
		i = 0;
		while (i < data->max_element_id)
		{
			if (poly_tab[i] == IN && is_edge_in_polygon(&data->elements[i].polygon, &data->edges[*edge_id]))
			{
				(*edge_id)++;
				return (&data->edges[*edge_id - 1]);
			}
			i++;
		}
		(*edge_id)++;
	}
	return (NULL);
}

t_element		*get_result(t_data *data, enum e_poly_tab *poly_tab)
{
	uint32_t	i;

	i = 0;
	while (i < data->max_element_id)
	{
		if (poly_tab[i] == IN)
			return (&data->elements[i]);
		i++;
	}
	return (NULL);
}
uint16_t		poly_tab_nbr(t_data *data, enum e_poly_tab *poly_tab)
{
	uint32_t	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < data->max_element_id)
	{
		if (poly_tab[i] == IN)
			ret++;
		i++;
	}
	return (ret);
}

void		init_poly_tab(t_data *data, enum e_poly_tab	*poly_tab, t_ivec2 *point)
{
	uint32_t i;
	i = 0;
	while (i < data->max_element_id)
	{
		if (!data->elements[i].enabled || !data->elements[i].polygon.finished)
		{
			i++;
			continue ;
		}
		if (is_in_polygon(point, &data->elements[i].polygon, NULL) != -1)
			poly_tab[i] = IN;
		else
			poly_tab[i] = OUT;
		i++;
	}
}

t_edge		*find_nearest_edge_between_points(t_data *data, t_ivec2 *point, t_ivec2 *last, enum e_poly_tab *poly_tab)
{
	t_edge		*ret;
	t_edge		*tmp_edge;
	float		tmp_dist;
	float		min;
	uint32_t	i;

	i = 0;
	min = -1.f;
	ret = NULL;
	while (i < data->max_element_id)
	{
		if (poly_tab[i] == IN)
		{
			tmp_dist = first_intersect_dist_in_poly(&data->elements[i].polygon, point, last, &tmp_edge);
			if ((tmp_dist < min || min == -1.f) && tmp_dist != -1)
			{
				min = tmp_dist;
				ret = tmp_edge;
			}
		}
		i++;
	}
	return (ret);
}

t_element	*get_polygon_from_point(t_data *data, t_ivec2 *point)
{
	t_edge			*touched_edge;
	t_edge			*tmp;
	t_ivec2			middle;
	enum e_poly_tab	*poly_tab;
	uint16_t		edge_id;
	t_element		*rez;

	poly_tab = malloc(sizeof(enum e_poly_tab) * data->max_element_id);
	init_poly_tab(data, poly_tab, point);
	edge_id = 0;
	while (poly_tab_nbr(data, poly_tab) > 1)
	{
		touched_edge = find_next_edge(data, poly_tab, &edge_id);
		middle = find_middle_edge(touched_edge);
		tmp = find_nearest_edge_between_points(data, point, &middle, poly_tab);
		if (tmp && tmp != touched_edge)
		{
			printf("The edge %ld touches another polygon. continuing.\n", touched_edge - data->edges);
			if (tmp == NULL)
				printf("tmp is NULL\n");
			else
				printf("tmp id : %ld\n", tmp - data->edges);
			continue ;
		}
		update_poly_tab(data, poly_tab, touched_edge);
	}
	rez = get_result(data, poly_tab);
	free(poly_tab);
	if (rez == NULL)
		printf("No polygon found\n");
	else
		printf("Polygon %d found\n", rez->id);
	return (rez);
}
