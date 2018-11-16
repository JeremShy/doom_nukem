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
			printf("data->point[i] = %d, %d\n", data->points[i].x, data->points[i].y);	
			printf("new_point = %d, %d\n", new_point->x, new_point->y);
			return (&data->points[i]);
		}
		i++;
	}
	ft_putendl_fd("Error : No space left on Points", 2);
	exit(EXIT_FAILURE);
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
		polygon->points[0] = new_point;
		(polygon->nb_points)++;
		put_pixel_to_image(&data->imgs[IMAGE_TEST], new_point->x,
			new_point->y, get_color_from_typewall(data->input.wall_type));
		printf("poli = %d : %d, %d\n", polygon->nb_points, (*polygon->points[0]).x, (*polygon->points[0]).y);
		return ;
	}
	else if (p == MIDDLE)
	{
		polygon->points[polygon->nb_points] = new_point;
		polygon->edges[polygon->nb_points - 1] = add_edge(data, (t_edge){1, data->input.wall_type, data->input.id_texture});
		(polygon->nb_points)++;
	}
	else if (p == END)
	{
		polygon->finished = 1;
		polygon->edges[polygon->nb_points - 1] = add_edge(data, (t_edge){1, data->input.wall_type, data->input.id_texture});
	}
	draw_line(polygon->points[polygon->nb_points - (p == MIDDLE ? 2 : 1)], new_point, &data->imgs[IMAGE_TEST],
		get_color_from_typewall(data->input.wall_type));
}

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
			add_seg(data, polygon, new_point, END);
		else if (!is_point_in_polygon(new_point, polygon))
			add_seg(data, polygon, new_point, MIDDLE);
	}
	if (polygon->nb_points == last_nbr)
		printf("No point was added.\n");
	print_points_list(data);
}
