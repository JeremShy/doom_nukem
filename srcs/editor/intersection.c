#include <editor.h>

uint32_t nb_intersec_in_poly(const t_polygon *polygon, const t_ivec2 *new_point, const t_ivec2 *last_point)
{
	uint32_t		current_edge;
	uint32_t		nb_intersec;
	t_intersection	intersec;

	current_edge = 0;
	nb_intersec = 0;

	while (current_edge < polygon->nb_points - (polygon->finished ? 0: 1))
	{
		if ((intersec = is_intersect(*polygon->edges[current_edge]->p1, *polygon->edges[current_edge]->p2, *last_point, *new_point)).intersect)
			nb_intersec++;
		current_edge++;
	}
	return (nb_intersec);
}

float	first_intersect_dist_in_poly(const t_polygon *polygon, const t_ivec2 *new_point, const t_ivec2 *last_point)
{
	uint32_t		current_edge;
	float			dist;
	t_intersection	intersec;

	current_edge = 0;
	dist = -1;
	while (current_edge < polygon->nb_points)
	{
		if ((intersec = is_intersect(*polygon->edges[current_edge]->p1, *polygon->edges[current_edge]->p2, *last_point, *new_point)).intersect)
		{
			if (get_idist(new_point, &intersec.intersection_point) < dist || dist == -1)
				dist = get_idist(new_point, &intersec.intersection_point);
		}
		current_edge++;
	}
	return (dist);
}
