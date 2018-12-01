#include <editor.h>

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

uint8_t		same_edges(const t_ivec2 *a1, const t_ivec2 *a2, const t_ivec2 *b1, const t_ivec2 *b2)
{
	return (is_equ_ivec2(a1, b1) && is_equ_ivec2(a2, b2)) || (is_equ_ivec2(a1, b2) && is_equ_ivec2(a2, b1));
}

t_ivec2		get_grid_point(t_ivec2 point)
{
	point.x = point.x + ((point.x % GRID_ROUND < GRID_ROUND / 2) ? -point.x % GRID_ROUND : GRID_ROUND - point.x % GRID_ROUND);
	point.y = point.y + ((point.y % GRID_ROUND < GRID_ROUND / 2) ? -point.y % GRID_ROUND : GRID_ROUND - point.y % GRID_ROUND);
	clamp(&point.x, 10, DRAWING_ZONE_WIDTH);
	clamp(&point.y, 10, WIN_SIZE_Y - 1 - 10);
	return (point);
}

uint32_t	get_nearest_point(t_data *data, t_ivec2 *point, int32_t *id)
{
	uint32_t	i;
	uint32_t	dist;
	uint32_t	tmp;

	i = 0;
	dist = -1u;
	*id = -1;
	while (i < MAX_POINTS_NBR)
	{
		if (data->used_point[i] > 0)
			if ((tmp = idist(point, &data->points[i])) < dist)
			{
				*id = i;
				dist = tmp;
			}
		i++;
	}
	return (dist);
}

uint8_t		is_equ_ivec2(const t_ivec2 *p1, const t_ivec2 *p2)
{
	return ((p1->x == p2->x) && (p1->y == p2->y));
}

uint32_t	get_idpoint_from_addr(const t_ivec2 *point, t_data *data)
{
	return (point - data->points);
}
