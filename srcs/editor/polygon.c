#include <editor.h>

void	clicked_polygon(t_data *data, int id)
{
	(void)data;
	(void)id;
	printf("in polygon_on_click.\n");
}

int8_t	is_in_polygon(int x, int y, t_element rect)
{
	(void)x;
	(void)y;
	(void)rect;
	return (0);
}

uint32_t	find_next_available(t_data *data)
{
	int	i;

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

float	get_idist(t_ivec2 p1, t_ivec2 p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

void	add_edge(t_data *data, t_polygon *polygon, t_ivec2 new_point)
{
	polygon->points[polygon->nb_points] = new_point;
	polygon->edges[polygon->nb_points - 1] = (t_edge){data->input.wall_type, data->input.id_texture};
	(polygon->nb_points)++;
}

uint32_t	get_color_from_typewall(t_edge_type t)
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

uint8_t check_segment(t_polygon polygon, t_ivec2 new_point)
{
	uint32_t	i;

	i = (polygon.points[0].x == new_point.x && polygon.points[0].y == new_point.y) ? 2 : 1;
	while (i < polygon.nb_points - 1)
	{
		if (is_intersect(polygon.points[i - 1], polygon.points[i], polygon.points[polygon.nb_points - 1], new_point))
		{
			printf("Intersection error between {{%d, %d}, {%d, %d}} and {{%d, %d}, {%d, %d}}\n", 
				polygon.points[i - 1].x, polygon.points[i - 1].y,
				polygon.points[i].x, polygon.points[i].y,
				polygon.points[polygon.nb_points - 1].x, polygon.points[polygon.nb_points - 1].y,
				new_point.x, new_point.y);
			return (0);
		}
		i++;
	}
	return (1);
}

t_polygon	draw_edge(t_data *data, t_ivec2 new_point)
{
	static	t_polygon polygon = {0, 0, {{0, 0}}, {{SOLID, -1}}};
	uint32_t	last_nbr;

	if (polygon.finished)
		polygon = (t_polygon){0, 0, {{0, 0}}, {{SOLID, -1}}};
	last_nbr = polygon.nb_points;
	printf("nb_points : %d\n", polygon.nb_points);
	if (polygon.nb_points + 1 == MAX_POLYGON_EDGES)
		new_point = polygon.points[0];
	if (polygon.nb_points == 0)
	{
		polygon.points[0] = new_point;
		(polygon.nb_points)++;
		put_pixel_to_image(&data->imgs[IMAGE_TEST], new_point.x, new_point.y, get_color_from_typewall(data->input.wall_type));
	}
	else if (polygon.nb_points > 2 && get_idist(new_point, polygon.points[0]) < 10 && check_segment(polygon, polygon.points[0]))
	{
		polygon.finished = 1;
		polygon.edges[polygon.nb_points] = (t_edge){data->input.wall_type, data->input.id_texture};
		draw_line(polygon.points[polygon.nb_points - 1], polygon.points[0], &data->imgs[IMAGE_TEST],
			get_color_from_typewall(data->input.wall_type));
	}
	else if (check_segment(polygon, new_point) && get_idist(new_point, polygon.points[0]) > 10)
	{
		add_edge(data, &polygon, new_point);
		draw_line(polygon.points[polygon.nb_points - 2], new_point, &data->imgs[IMAGE_TEST],
			get_color_from_typewall(data->input.wall_type));
	}
	if (polygon.nb_points == last_nbr)
		printf("No point was added.\n");
	return (polygon);
}
