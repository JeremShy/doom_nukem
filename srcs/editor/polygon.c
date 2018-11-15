#include <editor.h>

void	print_click(t_data *data, uint16_t id)
{
	(void)data;
	printf("clicked element  : %u\n", id);
}

float	is_in_polygon(int x, int y, const t_polygon *polygon)
{
	if ((nb_intersec_in_poly(polygon, &(t_ivec2){x, y}, &(t_ivec2){-1, -1}) & 1) == 1)
	{
		return (dist_first_intersect(polygon, &(t_ivec2){x, y}, &(t_ivec2){-1, -1}));
	}
	return (-1);
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

	while (current_edge < polygon->nb_points - (polygon->finished ? 0: 1))
	{
		if (current_edge == polygon->nb_points - 1 && polygon->finished)
		{
			printf("1\n");
			p1 = polygon->points[current_edge];
			p2 = polygon->points[0];
		}
		else
		{
			printf("2\n");
			p1 = polygon->points[current_edge];
			p2 = polygon->points[current_edge + 1];
		}
		printf("current : %d nb_pomit : %d\n", current_edge, polygon->nb_points);
		printf("p1: %d,%d 	p2: %d,%d\n", p1->x, p1->y, p2->x, p2->y);
		if ((intersec = is_intersect(*p1, *p2, *last_point, *new_point)).intersect)
			nb_intersec++;
		current_edge++;
	}
	return (nb_intersec);
}

float	dist_first_intersect(const t_polygon *polygon, const t_ivec2 *new_point, const t_ivec2 *last_point)
{
	uint32_t		current_edge;
	const t_ivec2	*p1;
	const t_ivec2	*p2;
	float			dist;
	t_intersection	intersec;

	current_edge = 0;
	dist = -1;
	while (current_edge < polygon->nb_points)
	{
		if (current_edge == polygon->nb_points - 1 && polygon->finished)
		{
			p1 = polygon->points[current_edge];
			p2 = polygon->points[0];
		}
		else
		{
			p1 = polygon->points[current_edge];
			p2 = polygon->points[current_edge + 1];
		}
		if ((intersec = is_intersect(*p1, *p2, *last_point, *new_point)).intersect)
		{
			if (get_idist(new_point, &intersec.intersection_point) < dist || dist == -1)
				dist = get_idist(new_point, &intersec.intersection_point);
		}
		current_edge++;
	}
	return (dist);
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
			polygon = &data->elements[j].polygon;
			current_edge = 0;
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
				if (is_intersect(*p1, *p2, *last_point, *new_point))
				{
					printf("Intersection error between {{%d, %d}, {%d, %d}} and {{%d, %d}, {%d, %d}}\n", 
						p1->x, p1->y,
						p2->x, p2->y,
						last_point->x, last_point->y,
						new_point->x, new_point->y);
					return (0);
				}
				current_edge++;
			}
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
				if (get_idist(new_point, elem[i].polygon.points[j]) < 10)
					return (*elem[i].polygon.points[j]);
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
		if (is_equ_ivec2(point, polygon->points[i]))
			return (1);
		i++;
	}
	return (0);
}

uint8_t		draw_edge_error(t_data *data, t_polygon	**polygon)
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
		ft_putendl_fd("Error: Polygon already Finised!", 2);
		return (1);
	}
	return (0);
}

t_ivec2	*add_points(t_data *data, const t_ivec2 *new_point)
{
	uint32_t i;

	i = 0;
	while (i < MAX_POLYGON_EDGES * MAX_ELEMENT_NBR)
	{
		if (!data->used_point[i])
		{
			data->points[i] = *new_point;
			data->used_point[i] = 1;
			printf("data->point[i] = %d, %d\n", data->points[i].x, data->points[i].y);	
			printf("new_point = %d, %d\n", new_point->x, new_point->y);
			return (&data->points[i]);
		}
		i++;
	}
	ft_putendl_fd("Error : No space left on Points", 2);
	exit(EXIT_FAILURE);
}

t_edge	*add_edge(t_data *data, const t_edge new_edge)
{
	uint32_t i;

	i = 0;
	while (i < MAX_POLYGON_EDGES * MAX_ELEMENT_NBR)
	{
		if (!data->used_edge[i])
		{
			data->edges[i] = new_edge;
			data->used_edge[i] = 1;
			return (&data->edges[i]);
		}
		i++;
	}
	ft_putendl_fd("Error : No space left on Edge", 2);
	exit(EXIT_FAILURE);
}

void	add_seg(t_data *data, t_polygon *polygon, const t_ivec2 *new_point, enum e_edge_position p)
{
	if (p == BEGIN)
	{
		polygon->points[0] = add_points(data, new_point);
		(polygon->nb_points)++;
		put_pixel_to_image(&data->imgs[IMAGE_TEST], new_point->x,
			new_point->y, get_color_from_typewall(data->input.wall_type));
		printf("poli = %d : %d, %d\n", polygon->nb_points, (*polygon->points[0]).x, (*polygon->points[0]).y);
		return ;
	}
	else if (p == MIDDLE)
	{
		polygon->points[polygon->nb_points] = add_points(data, new_point);
		polygon->edges[polygon->nb_points - 1] = add_edge(data, (t_edge){data->input.wall_type, data->input.id_texture});
		(polygon->nb_points)++;
	}
	else if (p == END)
	{
		polygon->finished = 1;
		polygon->edges[polygon->nb_points - 1] = add_edge(data, (t_edge){data->input.wall_type, data->input.id_texture});
	}
	draw_line(polygon->points[polygon->nb_points - (p == MIDDLE ? 2 : 1)], new_point, &data->imgs[IMAGE_TEST],
		get_color_from_typewall(data->input.wall_type));
}

void		draw_edge(t_data *data, t_ivec2 new_point)
{
	uint32_t	last_nbr;
	t_polygon	*polygon;
	t_ivec2		point;

	if (draw_edge_error(data, &polygon))
		return ;
	last_nbr = polygon->nb_points;
	new_point = get_near_point(data->elements, data->nb_elements, &new_point);
	if (polygon->nb_points + 1 == MAX_POLYGON_EDGES)
		new_point = *polygon->points[0];
	if (polygon->nb_points == 0)
		add_seg(data, polygon, &new_point, BEGIN);
	point = *(polygon->points[polygon->nb_points - 1]);
	printf("%d %d\n", point.x, point.y);
	if (check_segment(data, &new_point, polygon->points[polygon->nb_points - 1]))
	{
		if (polygon->nb_points > 2 && is_equ_ivec2(polygon->points[0], &new_point))
			add_seg(data, polygon, &new_point, END);
		else if (!is_point_in_polygon(&new_point, polygon))
			add_seg(data, polygon, &new_point, MIDDLE);
	}
	if (polygon->nb_points == last_nbr)
		printf("No point was added.\n");
}
