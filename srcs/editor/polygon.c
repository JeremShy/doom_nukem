#include <editor.h>

void	print_click(t_data *data, uint16_t id)
{
	(void)data;
	printf("clicked element  : %u\n", id);
}

int8_t	is_in_polygon(int x, int y, const t_polygon *polygon)
{
	if ((nb_intersec_in_poly(polygon, &(t_ivec2){x, y}, &(t_ivec2){-1, -1}) & 1) == 1)
		return (1);
	return (0);
}

uint32_t nb_intersec_in_poly(const t_polygon *polygon, const t_ivec2 *new_point, const t_ivec2 *last_point)
{
	uint32_t		current_edge;
	const t_ivec2	*p1;
	const t_ivec2	*p2;
	uint32_t		nb_intersec;
	t_intersection	intersec;

	current_edge = 0;
	nb_intersec = 0;
	while (current_edge < polygon->nb_points)
	{
		if (current_edge == polygon->nb_points - 1 && polygon->finished)
		{
			p1 = &polygon->points[current_edge];
			p2 = &polygon->points[0];
		}
		else
		{
			p1 = &polygon->points[current_edge];
			p2 = &polygon->points[current_edge + 1];
		}
		if ((intersec = is_intersect(*p1, *p2, *last_point, *new_point)).intersect)
			nb_intersec++;
		current_edge++;
	}
	return (nb_intersec);
}

uint32_t	find_next_available(t_data *data)
{
	uint32_t	i;

	i = 0;
	while (i < data->nb_elements)
	{
		if (data->elements[i].enabled == 0)
			return (i);
		i++;
	}
	(data->nb_elements)++;
	return (data->nb_elements - 1);
}

float	get_idist(const t_ivec2 *p1, const t_ivec2 *p2)
{
	return (sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2)));
}

void	add_edge(const t_data *data, t_polygon *polygon, const t_ivec2 *new_point)
{
	polygon->points[polygon->nb_points] = *new_point;
	printf("nb_points : %d\n", polygon->nb_points);
	polygon->edges[polygon->nb_points - 1] = (t_edge){data->input.wall_type, data->input.id_texture};
	(polygon->nb_points)++;
}

uint32_t	get_color_from_typewall(enum e_edge_type t)
{
	uint32_t color;

	if (t == SOLID)
		color = get_color_code(255, 255, 255, 0);
	else if (t == PORTAL)
		color = get_color_code(255, 0, 0, 0);
	else
		color = get_color_code(0, 0, 0, 255);
	return (color);
}

uint8_t check_segment(const t_data *data, const t_ivec2 *new_point, const t_ivec2 *last_point)
{
	uint32_t		j;

	j = 0;
	while (j < data->nb_elements)
	{
		if (data->elements[j].enabled)
		{
			if (nb_intersec_in_poly(&data->elements[j].polygon, new_point, last_point))
				return (0);
		}
		j++;
	}
	return (1);
}

t_ivec2 get_near_point(const t_element *elem, uint32_t nb_element, const t_ivec2 *new_point)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < nb_element)
	{
		if (elem[i].enabled)
		{
			j = 0;
			while (j < elem[i].polygon.nb_points)
			{
				if (get_idist(new_point, &(elem[i].polygon.points[j])) < 10)
					return (elem[i].polygon.points[j]);
				j++;
			}
		}
		i++;
	}
	return (*new_point);
}

uint8_t		is_equ_ivec2(const t_ivec2 *p1, const t_ivec2 *p2)
{
	return ((p1->x == p2->x) && (p1->y == p2->y));
}

uint8_t		is_point_in_polygon(const t_ivec2 *point, const t_polygon *polygon)
{
	uint32_t	i;

	i = 0;
	while (i < polygon->nb_points)
	{
		if (is_equ_ivec2(point, &polygon->points[i]))
			return (1);
		i++;
	}
	return (0);
}

void		draw_edge(t_data *data, t_ivec2 new_point)
{
	uint32_t	last_nbr;
	t_polygon	*polygon;

	if (data->input.id_current_element == -1)
	{
		ft_putendl_fd("ID current element is -1. Error !", 2);
		exit(EXIT_FAILURE);
	}
	polygon = &(data->elements[data->input.id_current_element].polygon);
	if (polygon->finished)
	{
		printf("%d\n", polygon->finished);
		ft_putendl_fd("Error: Polygon already Finised!", 2);
		return ;
	}
	last_nbr = polygon->nb_points;
	new_point = get_near_point(data->elements, data->nb_elements, &new_point);
	if (polygon->nb_points + 1 == MAX_POLYGON_EDGES)
		new_point = polygon->points[0];
	if (polygon->nb_points == 0)
	{
		polygon->points[0] = new_point;
		(polygon->nb_points)++;
		put_pixel_to_image(&data->imgs[IMAGE_TEST], new_point.x, new_point.y, get_color_from_typewall(data->input.wall_type));
	}
	else if (polygon->nb_points > 2 && is_equ_ivec2(&polygon->points[0], &new_point) && check_segment(data, &polygon->points[0], &polygon->points[polygon->nb_points - 1]))
	{
		polygon->finished = 1;
		polygon->edges[polygon->nb_points - 1] = (t_edge){data->input.wall_type, data->input.id_texture};

		draw_line(&polygon->points[polygon->nb_points - 1], &polygon->points[0], &data->imgs[IMAGE_TEST],
			get_color_from_typewall(data->input.wall_type));
	}
	else if (check_segment(data, &new_point, &polygon->points[polygon->nb_points - 1]) && !is_point_in_polygon(&new_point, polygon))
	{
		add_edge(data, polygon, &new_point);
		draw_line(&polygon->points[polygon->nb_points - 2], &new_point, &data->imgs[IMAGE_TEST],
			get_color_from_typewall(data->input.wall_type));
	}
	if (polygon->nb_points == last_nbr)
		printf("No point was added.\n");
}
