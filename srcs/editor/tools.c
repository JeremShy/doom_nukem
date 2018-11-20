#include <editor.h>

float		is_in_polygon(int x, int y, const t_polygon *polygon)
{
	if ((nb_intersec_in_poly(polygon, &(t_ivec2){0, 0}, &(t_ivec2){x, y}) & 1) == 1)
	{
		printf("in polygon with %d points\n", polygon->nb_points);
		return (first_intersect_dist_in_poly(polygon, &(t_ivec2){0, 0}, &(t_ivec2){x, y}));
	}
	return (-1);
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

void	clamp(int32_t *point, int32_t min, int32_t max)
{
	*point < min ? (*point = min) : 0;
	*point > max ? (*point = max) : 0;
}

uint8_t	same_edges(const t_ivec2 *a1, const t_ivec2 *a2, const t_ivec2 *b1, const t_ivec2 *b2)
{
	return (is_equ_ivec2(a1, b1) && is_equ_ivec2(a2, b2)) || (is_equ_ivec2(a1, b2) && is_equ_ivec2(a2, b1));
}

t_ivec2	*get_near_point(t_data *data, t_ivec2 *new_point)
{
	uint32_t	i;

	i = 0;
	while (i < MAX_POINTS_NBR)
	{
		if (data->used_point[i] == 1)
		{
			if (get_idist(new_point, &data->points[i]) < 10)
			{
				return (&data->points[i]);
			}
		}
		i++;
	}
	new_point->x = new_point->x + ((new_point->x % GRID_ROUND < GRID_ROUND / 2) ? -new_point->x % GRID_ROUND : GRID_ROUND - new_point->x % GRID_ROUND);
	new_point->y = new_point->y + ((new_point->y % GRID_ROUND < GRID_ROUND / 2) ? -new_point->y % GRID_ROUND : GRID_ROUND - new_point->y % GRID_ROUND);
	clamp(&new_point->x, 0, WIN_SIZE_X - 1);
	clamp(&new_point->y, 0, WIN_SIZE_Y - 1);
	return (NULL);
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
