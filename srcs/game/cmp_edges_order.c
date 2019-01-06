#include <game.h>

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

	// if (!edges_intersect_x(data, e1, e2))
	// 	return (0);
	if (!common_point(e1, e2))
	{
		v1 = ft_vec2_sub(*e1->p1, *e2->p1);
		v2 = ft_vec2_sub(*e1->p1, *e2->p2);
		normal = ft_vec2_get_normal(ft_vec2_sub(*e1->p1, *e1->p2));
		dot1 = ft_vec2_dot(normal, v1);
		dot2 = ft_vec2_dot(normal, v2);
		if (dot1 * dot2 < 0)
			ft_swap_ptr((void**)&e1, (void**)&e2);
	}
	v1 = ft_vec2_sub(*e1->p1, *e2->p1);
	v2 = ft_vec2_sub(*e1->p1, (t_vec2){data->player.pos.x, data->player.pos.y});
	normal = ft_vec2_get_normal(ft_vec2_sub(*e1->p1, *e1->p2));
	dot1 = ft_vec2_dot(normal, v1);
	dot2 = ft_vec2_dot(normal, v2);
	if (dot1 * dot2 < 0)
		return (-1);
	else
		return (1);
}
