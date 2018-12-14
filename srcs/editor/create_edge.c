#include <editor.h>

static uint8_t		create_edge_error(t_data *data, t_polygon	**polygon)
{
	if (data->input.id_current_element == -1)
	{
		ft_putendl_fd("ID current element is -1. Error !", 2);
		return (1);
	}
	*polygon = &(data->elements[data->input.id_current_element].polygon);
	if ((*polygon)->finished)
	{
		ft_putendl_fd("Error: Polygon already Finished!", 2);
		return (1);
	}
	return (0);
}

static int8_t	merge_edge(t_data *data, t_edge **edge)
{
	uint32_t	i;
	uint32_t	j;
	t_polygon	*poly;
	t_element *elements;
	
	elements = data->elements;
	i = 0;
	while (i < data->max_element_id)
	{
		if (!elements[i].enabled)
		{
			i++;
			continue ;
		}
		j = 0;
		poly = &elements[i].polygon;
		while (j < poly->nb_points)
		{
			if (poly->edges[j] != *edge && same_edges(poly->edges[j]->p1, poly->edges[j]->p2, (*edge)->p1, (*edge)->p2))
			{
				poly->edges[j]->p2 = (*edge)->p2;
				poly->edges[j]->p1 = (*edge)->p1;
				(*edge)->used = 0;
				(poly->edges[j]->used)++;
				*edge = poly->edges[j];
				(*edge)->type = data->input.wall_type;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static uint8_t		check_same_poly(t_data *data, t_polygon *poly, uint8_t *hash)
{
	int i;
	i = 0;
	while (i < poly->nb_points)
	{
		if (!hash[poly->edges[i] - data->edges])
			return (0);
		i++;
	}
	return (1);
}

uint8_t	polygon_already_exists(t_data *data, t_polygon *polygon)
{
	uint16_t	i;
	uint8_t		*hash;

	i = 0;
	hash = malloc(data->max_edge_id);
	ft_bzero(hash, data->max_edge_id);
	while (i < polygon->nb_points)
	{
		hash[polygon->edges[i] - data->edges] = 1;
		i++;
	}
	i = 0;
	while (i < data->max_element_id)
	{
		if (data->elements[i].enabled && &data->elements[i].polygon != polygon
			&& data->elements[i].polygon.nb_points == polygon->nb_points)
		{
			if (check_same_poly(data, &data->elements[i].polygon, hash))
				return (1);
		}
		i++;
	}
	free(hash);
	return (0);
}

static void	add_seg(t_data *data, t_polygon *polygon, t_ivec2 *new_point, enum e_edge_position p)
{
	t_ivec2	**new;
	t_edge	*old_edge;

	if (p == BEGIN)
	{
		polygon->edges[0] = add_edge(data, (t_edge){1, SOLID, new_point, NULL, data->input.texture_up, data->input.texture_down, data->input.texture_wall});
		(polygon->nb_points)++;
		return ;
	}
	if (polygon->edges[polygon->nb_points - 1]->p2 == NULL)
	{
		new = &(polygon->edges[polygon->nb_points - 1]->p2);
		polygon->edges[polygon->nb_points - 1]->p2 = new_point;
	}
	else
	{
		new = &(polygon->edges[polygon->nb_points - 1]->p1);
		polygon->edges[polygon->nb_points - 1]->p1 = new_point;
	}
	old_edge = polygon->edges[polygon->nb_points - 1];
	if (!merge_edge(data, &polygon->edges[polygon->nb_points - 1]))
	{
		*new = NULL;
		delete_point(new_point, data);
		return ;
	}
	if (p == MIDDLE)
	{
		polygon->edges[polygon->nb_points] = add_edge(data, (t_edge){1, SOLID, polygon->edges[polygon->nb_points - 1]->p2, NULL, data->input.texture_up, data->input.texture_down, data->input.texture_wall});
		(polygon->nb_points)++;
	}
	else if (p == END)
	{
		if (polygon_already_exists(data, polygon))
		{
			printf("This polygon already exists !\n");
			*new = NULL;
			polygon->edges[polygon->nb_points - 1]->used--;
			polygon->edges[polygon->nb_points - 1] = old_edge;
			polygon->edges[polygon->nb_points - 1]->used++;
			delete_point(new_point, data);
			return ;
		}
		polygon->finished = 1;
		delete_point(new_point, data);
	}
	polygon->edges[polygon->nb_points - (p == MIDDLE ? 2 : 1)]->type = data->input.wall_type;
	draw_line(polygon->edges[polygon->nb_points - (p == MIDDLE ? 2 : 1)]->p1, new_point, &data->imgs[IMG_DRAWING],
		get_color_from_typewall(data->input.wall_type));
}

static t_ivec2	*change_point(t_data *data, t_ivec2 *point)
{
	int32_t id;

	// *point = get_grid_point(*point);
	if (get_nearest_point(data, point, &id) < 13 && id != -1)
	{
		point = &data->points[id];
		data->used_point[id]++;
		return (point);
	}
	return (NULL);
}

void		create_edge(t_data *data, t_ivec2 click)
{
	t_polygon	*polygon;
	t_ivec2		*ptr;

	if (create_edge_error(data, &polygon))
		return ;
	ptr = change_point(data, &click);
	if (!ptr)
		if (!check_point(data, &click, NULL))
			return ;
	if (!ptr)
		ptr = add_points(data, &click);
	if (polygon->nb_points == 0 || check_segment(data, ptr, polygon->edges[polygon->nb_points - 1]->p1))
	{
		if (polygon->nb_points == 0)
		{
			add_seg(data, polygon, ptr, BEGIN);
		}
		else if (polygon->nb_points > 2 && polygon->edges[0]->p1 == ptr)
			add_seg(data, polygon, ptr, END);
		else if (!is_point_in_polygon(ptr, polygon))
			add_seg(data, polygon, ptr, MIDDLE);
		else
			delete_point(ptr, data);
	}
	else if (polygon->nb_points)
		delete_point(ptr, data);
}
