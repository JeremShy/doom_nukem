#include <editor.h>

static float	first_intersect_dist_in_poly(const t_polygon *polygon, const t_ivec2 *new_point, const t_ivec2 *last_point, t_edge **touched_edge)
{
	uint32_t		current_edge;
	float			dist;
	float			tmp_dist;
	t_intersection	intersec;
	t_intersection	min;

	current_edge = 0;
	dist = -1;
	while (current_edge < polygon->nb_points)
	{
		if ((intersec = intersect_two_segments(*polygon->edges[current_edge]->p1, *polygon->edges[current_edge]->p2, *last_point, *new_point)).intersect)
		{
			tmp_dist = idist(new_point, &intersec.intersection_point);
			if (tmp_dist < dist || dist == -1)
			{
				dist = tmp_dist;
				min = intersec;
				if (touched_edge)
					*touched_edge = polygon->edges[current_edge];
			}
		}
		current_edge++;
	}
	return (dist);
}

uint32_t nb_intersec_in_poly(const t_polygon *polygon, const t_ivec2 *new_point, const t_ivec2 *last_point)
{
	uint32_t		current_edge;
	uint32_t		nb_intersec;
	t_intersection	intersec;

	current_edge = 0;
	nb_intersec = 0;
	while (current_edge < polygon->nb_points - (polygon->finished ? 0 : 1))
	{
		if ((intersec = intersect_two_segments(*polygon->edges[current_edge]->p1, *polygon->edges[current_edge]->p2, *last_point, *new_point)).intersect)
			nb_intersec++;
		current_edge++;
	}
	return (nb_intersec);
}


float		is_in_polygon(const t_ivec2 *point, const t_polygon *polygon, t_edge **touched_edge)
{
	if (nb_intersec_in_poly(polygon, point, &(t_ivec2){0, 0}) & 1)
	{
		return (first_intersect_dist_in_poly(polygon, point, &(t_ivec2){0, 0}, touched_edge));
	}
	return (-1);
}


uint8_t		is_point_in_polygon(const t_ivec2 *point, const t_polygon *polygon)
{
	uint32_t	i;

	i = 0;
	while (i < polygon->nb_points)
	{
		if (is_equ_ivec2(point, polygon->edges[i]->p1))
			return (1);
		i++;
	}
	return (0);
}
