#include <game.h>

uint8_t interval_intersect(float a1, float a2, float b1, float b2)
{
		float	mini;
		float	maxi;

		mini = fmin(a1, a2);
		maxi = fmax(a1, a2);
		if (b1 <= mini && b2 <= mini)
				return (0);
		if (b1 >= maxi && b2 >= maxi)
				return (0);
		return (1);
}

uint8_t edges_intersect_x(t_data *data, t_edge *e1, t_edge *e2)
{
		float	e1p1;
		float	e1p2;
		float	e2p1;
		float	e2p2;

		e1p1 = data->project_normal[e1->p1 - data->points];
		e1p2 = data->project_normal[e1->p2 - data->points];

		if (fmax(e1p1, e1p2) - fmin(e1p1, e1p2) >= M_PI)
		{
			if (e1p1 < 0)
				e1p1 = M_PI + (M_PI + e1p1);
			else
				e1p2 = M_PI + (M_PI + e1p2);
		}

		e2p1 = data->project_normal[e2->p1 - data->points];
		e2p2 = data->project_normal[e2->p2 - data->points];
		return (interval_intersect(e1p1, e1p2, e2p1, e2p2));
}

uint8_t	common_point(t_edge *e1, t_edge *e2)
{
	if (e1->p1 == e2->p1 || e1->p1 == e2->p2 || e1->p2 == e2->p1 || e1->p2 == e2->p2)
		return (1);
	return (0);
}

void		ft_swap_ptr(void **ptr1, void **ptr2)
{
	void	*tmp;
	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

int8_t		cmp_edges_order(t_data *data, t_edge *e1, t_edge *e2)
{
	t_vec2	v1;
	t_vec2	v2;
	t_vec2	normal;
	float	dot1;
	float	dot2;
	char	tmp;

	// if (e1->id == 9 || e1->id == 10 || e2->id == 9 || e2->id == 10)
	{
		do_log("Comparing %d and %d\n", e1->id, e2->id);
	}
	if (!edges_intersect_x(data, e1, e2))
		return (0);
	tmp = 1;
	if (!common_point(e1, e2))
	{
		v1 = ft_vec2_sub(*e2->p2, *e1->p1);
		v2 = ft_vec2_sub(*e2->p1, *e1->p1);
		normal = ft_vec2_get_normal(ft_vec2_sub(*e1->p1, *e1->p2));
		dot1 = ft_vec2_dot(normal, v1);
		dot2 = ft_vec2_dot(normal, v2);
		if (dot1 * dot2 < 0)
		{
			tmp = -1;
			ft_swap_ptr((void**)&e1, (void**)&e2);
		}
	}
	v1 = ft_vec2_sub(*e2->p2, *e1->p1);
	if (v1.x == 0 && v1.y == 0)
		v1 = ft_vec2_sub(*e2->p1, *e1->p1);
	v2 = ft_vec2_sub((t_vec2){data->player.pos.x, data->player.pos.y}, *e1->p1);
	normal = ft_vec2_get_normal(ft_vec2_sub(*e1->p1, *e1->p2));
	dot1 = ft_vec2_dot(normal, v1);
	dot2 = ft_vec2_dot(normal, v2);

	// if (dot1 == 0 || dot2 == 0)
	// {
		// printf("v1 = {%f, %f}\nv2 = {%f, %f}\ndot1 = %f, dot2 = %f\n", v1.x, v1.y, v2.x, v2.y, dot1, dot2);
		// exit(0);
	// }

	if (dot1 * dot2 * tmp <= 0)
	{
		// if (e1->id == 9 || e1->id == 10 || e2->id == 9 || e2->id == 10)
			do_log("Returning -1\n");
		return (-1);
	}
	else
	{
		// if (e1->id == 9 || e1->id == 10 || e2->id == 9 || e2->id == 10)
			do_log("Returning 1\n");
		return (1);
	}
}
