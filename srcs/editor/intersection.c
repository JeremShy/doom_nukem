#include <editor.h>

uint32_t nb_intersec_in_poly(const t_polygon *polygon, const t_ivec2 *new_point, const t_ivec2 *last_point)
{
	uint32_t		current_edge;
	const t_ivec2	*p1;
	const t_ivec2	*p2;
	uint32_t		nb_intersec;
	t_intersection	intersec;

	current_edge = 0;
	nb_intersec = 0;
	// printf("testing segment : {%d,%d} and {%d,%d}\n", new_point->x, new_point->y, last_point->x, last_point->y);
	// printf("last_point : %d;%d\n", last_point->x, last_point->y);

	while (current_edge < polygon->nb_points - (polygon->finished ? 0: 1))
	{
		if (current_edge == polygon->nb_points - 1 && polygon->finished)
		{
			// printf("1\n");
			p1 = polygon->points[current_edge];
			p2 = polygon->points[0];
		}
		else
		{
			// printf("2\n");
			p1 = polygon->points[current_edge];
			p2 = polygon->points[current_edge + 1];
		}
		// printf("current : %d nb_pomit : %d\n", current_edge, polygon->nb_points);
		// printf("p1: %d,%d 	p2: %d,%d\n", p1->x, p1->y, p2->x, p2->y);
		if ((intersec = is_intersect(*p1, *p2, *last_point, *new_point)).intersect)
		{
			// printf("intersect !\n");
			nb_intersec++;
		}
		else
		{
			// printf("no intersect !\n");
		}
		current_edge++;
	}
	// printf("total nb : %u\n", nb_intersec);
	return (nb_intersec);
}

float	first_intersect_dist_in_poly(const t_polygon *polygon, const t_ivec2 *new_point, const t_ivec2 *last_point)
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
			// printf("intersection_point of polygon with %d points : %d %d\n", polygon->nb_points, intersec.intersection_point.x, intersec.intersection_point.y);
			// printf("Distance is : %f\n", get_idist(last_point, &intersec.intersection_point));
			if (get_idist(last_point, &intersec.intersection_point) < dist || dist == -1)
				dist = get_idist(last_point, &intersec.intersection_point);
		}
		current_edge++;
	}
	return (dist);
}
