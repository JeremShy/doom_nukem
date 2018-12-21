#include <game.h>

static void	ptr_swap(void **p1, void **p2)
{
	void	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void		get_p1_p2(t_data *data, t_edge *e1, t_vec2	*p1, t_vec2	*p2)
{
	if (ft_vec2_dot((t_vec2){data->player.dir.x, data->player.dir.y}, ft_vec2_sub(*e1->p1, (t_vec2){data->player.pos.x, data->player.pos.y})) > 0)
	{
		*p1 = *e1->p1;
		*p2 = *e1->p2;
	}
	else
	{
		*p1 = *e1->p2;
		*p2 = *e1->p1;
	}
}


// 1	: player du cote de e1
// 2	: player du cote de e2
t_edge		*is_edges_intersect(t_data *data, t_edge *e1, t_edge *e2)
{
	t_vec2	v1;
	t_vec2	v2;
	t_vec2	p1;
	t_vec2	p2;
	t_vec2	dir;
	t_vec2	norm;
	float	dot1;
	float	dot2;

	get_p1_p2(data, e1, &p1, &p2);
	dir = ft_vec2_sub(p2, p1);
	v1 = ft_vec2_sub(*e2->p1, p1);
	v2 = ft_vec2_sub(*e2->p2, p1);
	ft_vec2_normalize(&v1);
	ft_vec2_normalize(&v2);
	ft_vec2_normalize(&dir);
	norm = ft_vec2_get_normal(dir);
	dot1 = ft_vec2_dot(norm, v1);
	dot2 = ft_vec2_dot(norm, v2);
	if (dot1 * dot2 <= 0)
	{
		// Il faut changer: e2 delimiteur
		ptr_swap((void**)&e1, (void**)&e2);
		get_p1_p2(data, e1, &p1, &p2);
		dir = ft_vec2_sub(p2, p1);
		v1 = ft_vec2_sub(*e2->p1, p1);
		ft_vec2_normalize(&v1);
		ft_vec2_normalize(&dir);
		norm = ft_vec2_get_normal(dir);
		dot1 = ft_vec2_dot(norm, v1);
	}
	v2 = ft_vec2_sub((t_vec2){data->player.pos.x, data->player.pos.y}, p1);
	dot2 = ft_vec2_dot(norm, v2);
	if (dot1 * dot2 <= 0)
		return (e1);
	return (e2);
}
