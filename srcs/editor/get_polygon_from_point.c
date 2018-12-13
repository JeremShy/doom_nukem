#include <editor.h>

t_element	*find_other_elem_with_edge(t_data *data, t_edge *edge, t_element *except)
{
	uint16_t	i;
	uint16_t	j;

	i = 0;
	while (i < data->nb_elements)
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
	while (i < data->nb_elements)
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

t_edge		*get_dist_middle_edge_and_point(t_edge *edge_1, t_edge *edge_2, t_ivec2 *point)
{
	float	dist_1;
	float	dist_2;
	t_ivec2	point_1;
	t_ivec2	point_2;

	point_1 = (t_ivec2){(edge_1->p1->x + edge_1->p2->x) / 2, (edge_1->p1->y + edge_1->p2->y) / 2};
	point_2 = (t_ivec2){(edge_2->p1->x + edge_2->p2->x) / 2, (edge_2->p1->y + edge_2->p2->y) / 2};
	dist_1 = idist(&point_1, point);
	dist_2 = idist(&point_2, point);
	return (dist_1 < dist_2 ? edge_1 : edge_2);
}

t_element	*get_polygon_from_point(t_data *data, t_ivec2 *point)
{
	float		dist;
	int			id;
	t_element	*other_element;
	t_edge		*touched_edge;
	t_edge		*not_common_edge_1;
	t_edge		*not_common_edge_2;

	touched_edge = find_a_nearby_polygon(data, &id, &dist, point);
	if (dist == -1)
		return (NULL);
	printf("touched edge has id : %ld\n", touched_edge - data->edges);
	if (touched_edge->used == 1)
		return (&data->elements[id]);
	other_element = find_other_elem_with_edge(data, touched_edge, &data->elements[id]);
	if (!is_in_polygon(point, &other_element->polygon, NULL))
		return (&data->elements[id]);
	not_common_edge_1 = get_edge_not_common(&data->elements[id].polygon, &other_element->polygon);
	not_common_edge_2 = get_edge_not_common(&other_element->polygon, &data->elements[id].polygon);
	if (get_dist_middle_edge_and_point(not_common_edge_1, not_common_edge_2, point) == not_common_edge_1)
		return (&data->elements[id]);
	else
		return (other_element);
}
