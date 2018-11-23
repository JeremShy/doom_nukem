#include <editor.h>

static float	get_idist_seg_point(t_ivec2 p1, t_ivec2 p2, t_ivec2 p3, t_ivec2 *p4)
{
	float	angle;
	float	ha;
	float	hc;
	float	dist;

	if ((angle = iangle(vec_from_points(&p1, &p2), vec_from_points(&p1, &p3))) > M_PI / 2)
	{
		printf("angle 1 = %f\n", angle / M_PI * 180);
		swap(&p1.x, &p2.x);
		swap(&p1.y, &p2.y);
		angle = iangle(vec_from_points(&p1, &p2), vec_from_points(&p1, &p3));
		printf("angle 2 = %f\n", angle / M_PI * 180);
	}
	printf("angle = %f\n", angle / M_PI * 180);
	ha = get_idist(&p1, &p3) * cos(angle) - get_idist(&p1, &p2);
	hc = get_idist(&p1, &p3) * sin(angle);
	printf("get_idist(&p1, &p3) = %f, sin(angle) = %f\n", get_idist(&p1, &p3), sin(angle));
	fclamp(&ha, 0, 1000);
	dist = sqrt(ha * ha + hc * hc);
	printf("ha = %f, hc = %f\n", ha, hc);
	*p4 = (t_ivec2){ha * vec_from_points(&p1, &p2).x / get_idist(&p1, &p2) + p1.x, ha * vec_from_points(&p1, &p2).y / get_idist(&p1, &p2) + p1.y};
	printf("p4->x = %d, p4->y = %d\n", p4->x, p4->y);
	return (dist);
}

t_edge			*get_nearest_edge(const t_ivec2 *point, t_edge *edges, t_ivec2 *p4)
{
	int			i;
	float		dist;
	float		min;
	uint32_t	id;
	t_edge		*tmp;

	i = 0;
	min = -1;
	while (i < MAX_POINTS_NBR)
	{
		tmp = &edges[i];
		if (tmp->used)
		{
			printf(".......\n");
			if ((dist = get_idist_seg_point(*tmp->p1, *tmp->p2, *point, p4)) < min || min == -1)
			{		
				min = dist;
				id = i;
			}
		}
		i++;
	}
	printf("min = %f\n", min);
	if (min == -1)
		return (NULL);
	return (&edges[id]);
}
