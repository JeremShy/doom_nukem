#include <editor.h>

static float	idist_seg_and_point(t_ivec2 p1, t_ivec2 p2, t_ivec2 p3)
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
	ha = idist(&p1, &p3) * cos(angle);
	hc = idist(&p1, &p3) * sin(angle);
	if (idist(&p1, &p3) * cos(angle) > idist(&p1, &p2))
		dist = sqrt((ha - idist(&p1, &p2)) * (ha - idist(&p1, &p2)) + hc * hc);
	else
		dist = hc;	
	return (dist);
}

t_edge			*get_nearest_edge_except(const t_ivec2 *point, t_data *data, float *min, t_ivec2 *exept)
{
	int			i;
	float		dist;
	uint32_t	id;
	t_edge		*tmp;

	i = 0;
	*min = -1;
	while (i < data->max_point_id)
	{
		tmp = &data->edges[i];
		if (tmp->used && tmp->p2 && tmp->p1 != exept && tmp->p2 != exept)
		{
			if ((dist = idist_seg_and_point(*tmp->p1, *tmp->p2, *point)) < *min || *min == -1)
			{
				*min = dist;
				id = i;
			}
		}
		i++;
	}
	if (*min == -1)
		return (NULL);
	return (&data->edges[id]);
}

t_edge			*get_nearest_edge(const t_ivec2 *point, t_data *data, float *min)
{
	int			i;
	float		dist;
	uint32_t	id;
	t_edge		*tmp;

	i = 0;
	*min = -1;
	while (i < data->max_point_id)
	{
		tmp = &data->edges[i];
		if (tmp->used && tmp->p2)
		{
			if ((dist = idist_seg_and_point(*tmp->p1, *tmp->p2, *point)) < *min || *min == -1)
			{
				*min = dist;
				id = i;
			}
		}
		i++;
	}
	if (*min == -1)
		return (NULL);
	return (&data->edges[id]);
}
