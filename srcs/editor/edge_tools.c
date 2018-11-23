#include <editor.h>

static float	get_idist_seg_point(t_ivec2 p1, t_ivec2 p2, t_ivec2 p3)
{
	float	angle;
	float	ha;
	float	hc;
	float	dist;

	if ((angle = iangle(vec_from_points(&p1, &p2), vec_from_points(&p1, &p3))) > M_PI / 2)
	{
		swap(&p1.x, &p2.x);
		swap(&p1.y, &p2.y);
		angle = iangle(vec_from_points(&p1, &p2), vec_from_points(&p1, &p3));
	}
	ha = get_idist(&p1, &p3) * cos(angle);
	hc = get_idist(&p1, &p3) * sin(angle);
	if (get_idist(&p1, &p3) * cos(angle) > get_idist(&p1, &p2))
		dist = sqrt((ha - get_idist(&p1, &p2)) * (ha - get_idist(&p1, &p2)) + hc * hc);
	else
		dist = hc;	
	return (dist);
}

t_edge			*get_nearest_edge_exept(const t_ivec2 *point, t_edge *edges, float *min, t_ivec2 *exept)
{
	int			i;
	float		dist;
	uint32_t	id;
	t_edge		*tmp;

	i = 0;
	*min = -1;
	while (i < MAX_POINTS_NBR)
	{
		tmp = &edges[i];
		if (tmp->used && tmp->p2 && tmp->p1 != exept && tmp->p2 != exept)
		{
			if ((dist = get_idist_seg_point(*tmp->p1, *tmp->p2, *point)) < *min || *min == -1)
			{
				*min = dist;
				id = i;
			}
		}
		i++;
	}
	if (*min == -1)
		return (NULL);
	return (&edges[id]);
}

t_edge			*get_nearest_edge(const t_ivec2 *point, t_edge *edges, float *min)
{
	int			i;
	float		dist;
	uint32_t	id;
	t_edge		*tmp;

	i = 0;
	*min = -1;
	while (i < MAX_POINTS_NBR)
	{
		tmp = &edges[i];
		if (tmp->used && tmp->p2)
		{
			if ((dist = get_idist_seg_point(*tmp->p1, *tmp->p2, *point)) < *min || *min == -1)
			{
				*min = dist;
				id = i;
			}
		}
		i++;
	}
	if (*min == -1)
		return (NULL);
	return (&edges[id]);
}