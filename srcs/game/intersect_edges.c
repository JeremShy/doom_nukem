#include <game.h>

static void	ptr_swap(void **p1, void **p2)
{
	void	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

// p1 must be a point in front of us, p2 may or may not be behind us. p1 and p2 belong to e1
void		get_p1_p2(t_data *data, t_edge *e1, t_vec2	*p1, t_vec2	*p2)
{
	float tmp;

	tmp = ft_vec2_dot((t_vec2){data->player.dir.x, data->player.dir.y}, ft_vec2_sub(*e1->p1, (t_vec2){data->player.pos.x, data->player.pos.y}));
	printf("tmp = %f\n", tmp);
	if (tmp > 0)
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

	printf("p1 = {{%f, %f}, {%f, %f}} et p2 = {{%f, %f}, {%f, %f}}\n", e1->p1->x, e1->p1->y, e1->p2->x, e1->p2->y, e2->p1->x, e2->p1->y, e2->p2->x, e2->p2->y);
	get_p1_p2(data, e1, &p1, &p2);

	dir = ft_vec2_sub(p2, p1); // direction of e1

	v1 = ft_vec2_sub(*e2->p1, p1);
	printf("v1 = {%f, %f}\n", v1.x, v1.y);
	v2 = ft_vec2_sub(*e2->p2, p1);
	ft_vec2_normalize(&v1);
	ft_vec2_normalize(&v2);
	ft_vec2_normalize(&dir);
	norm = ft_vec2_get_normal(dir);
	dot1 = ft_vec2_dot(norm, v1);
	dot2 = ft_vec2_dot(norm, v2);
	if (dot1 * dot2 <= 0)
	{
		printf("je passe ici\n");
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
