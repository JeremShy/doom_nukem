#include <editor.h>

static uint8_t		draw_edge_error(t_data *data, t_polygon	**polygon)
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

static t_ivec2	*add_points(t_data *data, const t_ivec2 *new_point)
{
	uint32_t i;

	i = 0;
	while (i < MAX_POLYGON_EDGES * MAX_ELEMENT_NBR)
	{
		if (!data->used_point[i])
		{
			data->points[i] = *new_point;
			data->used_point[i] = 1;
			// printf("data->point[i] = %d, %d\n", data->points[i].x, data->points[i].y);	
			// printf("new_point = %d, %d\n", new_point->x, new_point->y);
			return (&data->points[i]);
		}
		i++;
	}
	ft_putendl_fd("Error : No space left on Points", 2);
	exit(EXIT_FAILURE);
}

static t_edge	*edge_exists(t_element *elements, uint32_t nb_elements, t_ivec2 p1, t_ivec2 p2)
{
	uint32_t	i;
	uint32_t	j;
	t_polygon	*poly;

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
			if (j < poly->nb_points - 1)
			{
				if (same_edges(poly->points[j], poly->points[j + 1], &p1, &p2))
				{
					printf("edge exists !\n");
					return (poly->edges[j]);
				}
			}
			else if (poly->finished)
			{
				if (same_edges(poly->points[0], poly->points[j], &p1, &p2))
				{
					printf("edge exists 2!\n");
					return (poly->edges[j]);
				}
			}
			j++;
		}
		i++;
	}
	return (NULL);
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

static void	init_poly_colli(t_polygon *polygon, int32_t	tmp[MAX_COLLISION])
{
	int n;

	n = 0;
	polygon->in_element = -2;
	while (n < 10)
	{
		polygon->collision_element[n] = tmp[n];
		polygon->same_point_as_element[n] = -1;
		n++;
	}
}

static void	add_seg(t_data *data, t_polygon *polygon, t_ivec2 *new_point, enum e_edge_position p)
{
	if (p == BEGIN)
	{
		polygon->points[0] = new_point;
		(polygon->nb_points)++;
		put_pixel_to_image(&data->imgs[IMAGE_TEST], new_point->x,
			new_point->y, get_color_from_typewall(data->input.wall_type));
		printf("poli = %d : %d, %d\n", polygon->nb_points, (*polygon->points[0]).x, (*polygon->points[0]).y);
		return ;
	}
	else if (p == MIDDLE)
	{
		if ((polygon->edges[polygon->nb_points - 1] = edge_exists(data->elements, data->nb_elements, *polygon->points[polygon->nb_points - 1], *new_point)) == NULL)
		{
			polygon->edges[polygon->nb_points - 1] = add_edge(data, (t_edge){1, data->input.wall_type, data->input.id_texture});
		}
		polygon->points[polygon->nb_points] = new_point;
		(polygon->nb_points)++;
	}
	else if (p == END)
	{
		polygon->finished = 1;
		if ((polygon->edges[polygon->nb_points - 1] = edge_exists(data->elements, data->nb_elements, *polygon->points[polygon->nb_points - 1], *polygon->points[0])) == NULL)
		{
			polygon->edges[polygon->nb_points - 1] = add_edge(data, (t_edge){1, data->input.wall_type, data->input.id_texture});
		}
	}
	draw_line(polygon->points[polygon->nb_points - (p == MIDDLE ? 2 : 1)], new_point, &data->imgs[IMAGE_TEST],
		get_color_from_typewall(data->input.wall_type));
}

int		ft_poly_colli_len(int32_t	tab[MAX_COLLISION])
{
	int	n;

	n = 0;
	while (n < 10 && tab[n] != -1)
		n++;
	return (n);
}

int		ft_find_poly_colli(int32_t	tab[MAX_COLLISION], uint16_t	index)
{
	int	n;

	n = 0;
	while (n < 10 && tab[n] != -1)
	{
		if (tab[n] == index)
			return (n);
		n++;
	}
	return (-1);
}

void	ft_suppr_poly_colli(t_polygon *polygon, uint16_t	index)
{
	int	n;

	n = 0;
	while (n < 10 && (polygon->collision_element)[n] != -1)
	{
		if ((polygon->collision_element)[n] == index)
			while (n + 1 < 10 && (polygon->collision_element)[n] != -1)
			{
				(polygon->collision_element)[n] = (polygon->collision_element)[n + 1];
				n++;
			}
		n++;
	}
}

void	ft_suppr_poly_point(t_polygon *polygon, uint16_t	index)
{
	int	n;

	n = 0;
	while (n < 10 && (polygon->same_point_as_element)[n] != -1)
	{
		if ((polygon->same_point_as_element)[n] == index)
		{
			while (n + 1 < 10 && (polygon->same_point_as_element)[n] != -1)
			{
				(polygon->same_point_as_element)[n] = (polygon->same_point_as_element)[n + 1];
				n++;
			}
			return ;
		}
		n++;
	}
}

void	ft_print_poly_colli(t_polygon *polygon)
{
	int n = 0;

	while(n < ft_poly_colli_len(polygon->collision_element))
	{
		printf("collision avec l'element %d\n", polygon->collision_element[n]);
		n++;
	}
	n = 0;
	while(n < ft_poly_colli_len(polygon->same_point_as_element))
	{
		printf("point commun avec l'element %d\n", polygon->same_point_as_element[n]);
		n++;
	}
	if (polygon->in_element != -2)
		printf("dans l'element %d\n", polygon->in_element);
}

void	ft_find_in_element_poly(t_polygon *poly)
{
	int max;
	int n;

	n = 0;
	max = poly->in_element;
	while (n < 10)
	{
		if (poly->collision_element[n] > max)
			max = poly->collision_element[n];
		if (poly->same_point_as_element[n] > max)
			max = poly->same_point_as_element[n];
		n++;
	}
	poly->in_element = max;
}

void	ft_clean_poly_colli(t_polygon *polygon, int32_t tmp[MAX_COLLISION])
{
	int n;

	n = 0;
	while(n < ft_poly_colli_len(polygon->collision_element))
	{
		if (ft_find_poly_colli(tmp, polygon->collision_element[n]) == -1)
		{
			ft_suppr_poly_colli(polygon, polygon->collision_element[n]);
			n = -1;
		}
		n++;
	}
	n = 0;
	while(n < ft_poly_colli_len(polygon->same_point_as_element))
	{
		if (ft_find_poly_colli(tmp, polygon->same_point_as_element[n]) == -1)
		{
			ft_suppr_poly_point(polygon, polygon->same_point_as_element[n]);
			n = -1;
		}
		n++;
	}
	//ft_find_in_element_poly(polygon);
}

void ft_init_tmp(int32_t tmp[MAX_COLLISION])
{
	int n;

	n = 0;
	while (n < 10)
	{
		tmp[n] = -1;
		n++;
	}
}

void	add_to_tmp(t_data *data, int32_t tmp[MAX_COLLISION])
{
	int n;
	uint32_t i_element;

	n = 0;
	while (n < 10)
	{
		i_element = 0;
		while (i_element < data->nb_elements)
		{
			if (data->elements[i_element].id == tmp[n] && data->elements[i_element].polygon.in_element != -1)
				tmp[ft_poly_colli_len(tmp)] = data->elements[i_element].polygon.in_element;
			i_element++;
		}
		n++;
	}
}

t_intersection	point_find_between_2_existing_point(t_element element, int i_edges, int precision, t_ivec2 clicked_point)
{
	t_intersection intersection;

	if (i_edges == element.polygon.nb_points - 1)
	{
		intersection = is_intersect(*(element.polygon.points[i_edges]), *(element.polygon.points[0]), (t_ivec2){clicked_point.x - precision, clicked_point.y}, (t_ivec2){clicked_point.x + precision, clicked_point.y});
	}
	else
	{
		intersection = is_intersect(*(element.polygon.points[i_edges]), *(element.polygon.points[i_edges + 1]), (t_ivec2){clicked_point.x - precision, clicked_point.y}, (t_ivec2){clicked_point.x + precision, clicked_point.y});
	}
	return(intersection);
}

int		test(t_data *data, t_ivec2 clicked_point, int precision, t_polygon *poly)
{
	int i_element;
	int i_edges;
	t_intersection intersection;
	int ret;
	int32_t	tmp[MAX_COLLISION];

	ft_init_tmp(tmp);
	i_element = 0;
	ret = 0;
	while (i_element < (int)data->nb_elements)
	{
		if (data->elements[i_element].enabled && data->elements[i_element].clickable && data->elements[i_element].polygon.finished)
		{
			i_edges = 0;
			while(i_edges < data->elements[i_element].polygon.nb_points)
			{
				intersection = point_find_between_2_existing_point(data->elements[i_element], i_edges, precision, clicked_point);
				if ((data->elements[i_element].polygon.points[i_edges]->x == clicked_point.x && data->elements[i_element].polygon.points[i_edges]->y == clicked_point.y))
				{
					if (ft_find_poly_colli(tmp, i_element) == -1)
						tmp[ft_poly_colli_len(tmp)] = i_element;
					ret = 1;
				}
				else if (intersection.intersect == 1)
				{
					if (ft_find_poly_colli(tmp, i_element) == -1)
						tmp[ft_poly_colli_len(tmp)] = i_element;
					ret = 1;
				}
				i_edges++;
			}
		}
		i_element++;
	}
	add_to_tmp(data, tmp);
	if (poly->nb_points == 0)
		init_poly_colli(poly, tmp);
	if (poly->nb_points > 0)
		ft_clean_poly_colli(poly, tmp);
	if (ret == 0)
		poly->in_element = loop_elems(1, clicked_point.x, clicked_point.y, data);
	printf("In polygon : %d\n", poly->in_element);
	return (ret);
}

// uint8_t	check_point(const t_data *data, const t_ivec2 *new_point, t_polygon *polygon)
// {
// 	int sector_clicked;
// 	int n;

// 	sector_clicked = loop_elems(1, new_point.x,int new_point.y, data);
// 	n = 0;
// 	while ()
// }

void		draw_edge(t_data *data, t_ivec2 clicked_point)
{
	uint32_t	last_nbr;
	t_polygon	*polygon;
	t_ivec2		point;
	t_ivec2		*new_point;

	if (draw_edge_error(data, &polygon))
		return ;
	last_nbr = polygon->nb_points;
	new_point = get_near_point(data, &clicked_point);

	if (polygon->nb_points + 1 == MAX_POLYGON_EDGES)
		new_point = polygon->points[0];
	
	test(data, clicked_point, 3, polygon);
	
	if (polygon->nb_points == 0)
	{
		if (!new_point)
			new_point = add_points(data, &clicked_point);
		add_seg(data, polygon, new_point, BEGIN);
	}

	point = *(polygon->points[polygon->nb_points - 1]);
	printf("%d %d\n", point.x, point.y);
	if (check_segment(data, (new_point ? new_point : &clicked_point), polygon->points[polygon->nb_points - 1]))
	{
		if (!new_point)
			new_point = add_points(data, &clicked_point);
		if (polygon->nb_points > 2 && is_equ_ivec2(polygon->points[0], new_point))
		{
			printf("ending segment\n");
			add_seg(data, polygon, new_point, END);
			ft_find_in_element_poly(polygon);
			printf("Le polygon %d est dans le polygon %d\n", data->input.id_current_element, polygon->in_element);
		}
		else if (!is_point_in_polygon(new_point, polygon))
		{
			add_seg(data, polygon, new_point, MIDDLE);
		}
	}
	if (polygon->nb_points == last_nbr)
		printf("No point was added.\n");
	// print_edges_list(data);
}
