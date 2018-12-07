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
		printf("%d\n", (*polygon)->finished);
		ft_putendl_fd("Error: Polygon already Finished!", 2);
		return (1);
	}
	return (0);
}

static t_ivec2	*add_points(t_data *data, const t_ivec2 *new_point)
{
	uint32_t i;

	i = 0;
	while (i < MAX_POINTS_NBR)
	{
		if (!data->used_point[i])
		{
			data->points[i] = *new_point;
			data->used_point[i] = 1;
			return (&data->points[i]);
		}
		i++;
	}
	ft_putendl_fd("Error : No space left on Points", 2);
	exit(EXIT_FAILURE);
}

static void	edge_exists(t_data *data, uint32_t nb_elements, t_edge **edge)
{
	uint32_t	i;
	uint32_t	j;
	t_polygon	*poly;
	t_element *elements;
	
	elements = data->elements;
	i = 0;
	while (i < nb_elements)
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
				*edge = poly->edges[j];
				(*edge)->type = data->input.wall_type;
				return ;
			}
			j++;
		}
		i++;
	}
}

static t_edge	*add_edge(t_data *data, const t_edge new_edge)
{
	uint32_t i;

	i = 0;
	while (i < MAX_POLYGON_EDGES * MAX_ELEMENT_NBR)
	{
		if (!data->edges[i].used)
		{
			data->edges[i] = new_edge;
			data->edges[i].used = 1;
			return (&data->edges[i]);
		}
		i++;
	}
	ft_putendl_fd("Error : No space left on Edge", 2);
	exit(EXIT_FAILURE);
}

static void	add_seg(t_data *data, t_polygon *polygon, t_ivec2 *new_point, enum e_edge_position p)
{
	if (p == BEGIN)
	{
		polygon->edges[0] = add_edge(data, (t_edge){1, data->input.wall_type, data->input.texture_wall, new_point, NULL});
		(polygon->nb_points)++;
		put_pixel_to_image(&data->imgs[IMG_DRAWING], new_point->x,
			new_point->y, get_color_from_typewall(data->input.wall_type));
		return ;
	}
	polygon->edges[polygon->nb_points - 1]->p2 = new_point;
	edge_exists(data, data->nb_elements, &polygon->edges[polygon->nb_points - 1]);
	if (p == MIDDLE)
	{
		polygon->edges[polygon->nb_points] = add_edge(data, (t_edge){1, data->input.wall_type, data->input.texture_wall, polygon->edges[polygon->nb_points - 1]->p2, NULL});
		(polygon->nb_points)++;
	}
	else if (p == END)
	{
		polygon->finished = 1;
		delete_point(new_point, data);
	}
	draw_line(polygon->edges[polygon->nb_points - (p == MIDDLE ? 2 : 1)]->p1, new_point, &data->imgs[IMG_DRAWING],
		get_color_from_typewall(data->input.wall_type));
}

static t_ivec2 	*change_point(t_data *data, t_ivec2 *point)
{
	int32_t id;

	if (get_nearest_point(data, point, &id) < 10 && id != -1)
	{
		point = &data->points[id];
		data->used_point[id]++;
		return (point);
	}
	else
		*point = get_grid_point(*point);
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
			add_seg(data, polygon, ptr, BEGIN);
		else if (polygon->nb_points > 2 && is_equ_ivec2(polygon->edges[0]->p1, ptr))
			add_seg(data, polygon, ptr, END);
		else if (!is_point_in_polygon(ptr, polygon))
			add_seg(data, polygon, ptr, MIDDLE);
		else
			delete_point(ptr, data);
	}
	else if (polygon->nb_points)
		delete_point(ptr, data);
}
