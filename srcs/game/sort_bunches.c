#include <game.h>

uint8_t	interval_intersect(float a1, float a2, float b1, float b2)
{
	float		mini;
	float		maxi;

	mini = fmin(a1, a2);
	maxi = fmax(a1, a2);
	if (b1 < mini && b2 < mini)
		return (0);
	if (b1 > maxi && b2 > maxi)
		return (0);
	return (1);
}

uint8_t	edges_intersect_x(t_data *data, t_edge *e1, t_edge *e2)
{
	float	e1p1;
	float	e1p2;
	float	e2p1;
	float	e2p2;

	e1p1 = data->project_normal[e1->p1 - data->points];
	e1p2 = data->project_normal[e1->p2 - data->points];
	e2p1 = data->project_normal[e2->p1 - data->points];
	e2p2 = data->project_normal[e2->p2 - data->points];
	return (interval_intersect(e1p1, e1p2, e2p1, e2p2));
}

void	get_min_max(t_data *data, t_bunch *bunch, float *min, float *max)
{
	int			i;
	uint8_t		b;
	t_sector	*sec;
	float		p1;
	float		p2;

	sec = bunch->sector;
	i = bunch->id_begin;
	*min = data->project_normal[sec->edges[i]->p1 - data->points];
	*max = data->project_normal[sec->edges[i]->p1 - data->points];
	b = 1;
	while (b || i != (bunch->id_end + 1) % bunch->sector->nb_edges)
	{
		b = 0;
		p1 = data->project_normal[sec->edges[i]->p1 - data->points];
		p2 = data->project_normal[sec->edges[i]->p2 - data->points];

		if (p1 < *min)
			*min = p1;
		if (p1 > *max)
			*max = p1;

		if (p2 < *min)
			*min = p2;
		if (p2 > *max)
			*max = p2;
		i = (i + 1) % bunch->sector->nb_edges;
	}
}

uint8_t	same_side(t_player *player, t_edge *edge)
{
	float	dot1;
	float	dot2;
	t_vec2	v1;
	t_vec2	v2;

	v1 = ft_vec2_sub(*edge->p1, (t_vec2){player->pos.x, player->pos.y});
	v2 = ft_vec2_sub(*edge->p2, (t_vec2){player->pos.x, player->pos.y});
	dot1 = ft_vec2_dot((t_vec2){player->dir.x, player->dir.y}, v1);
	dot2 = ft_vec2_dot((t_vec2){player->dir.x, player->dir.y}, v2);
	return (dot1 * dot2 >= 0);
}

/*
** e1 and e2 are the two first overlapping walls
*/
t_ivec2	find_e1_e2(t_data *data, t_bunch *b1, t_bunch *b2)
{
	int		i;
	int		j;
	uint8_t	b;

	i = b1->id_begin;
	b = 1;
	while (b || i != (b1->id_end + 1) % b1->sector->nb_edges)
	{
		j = b2->id_begin;
		b = 1;
		while (b || j != (b2->id_end + 1) % b2->sector->nb_edges)
		{
			b = 0;
			if (edges_intersect_x(data, b1->sector->edges[i], b2->sector->edges[j]))
				return ((t_ivec2){b1->sector->edges[i]->id, b2->sector->edges[j]->id});
			j = (j + 1) % b2->sector->nb_edges;
		}
		b = 0;
		i = (i + 1) % b1->sector->nb_edges;
	}
	return ((t_ivec2){0, 0});
}

int8_t	handle_overlapping_bunches(t_data *data, t_bunch *b1, t_bunch *b2)
{
	t_edge	*e1;
	t_edge	*e2;
	t_ivec2	tmp;

	tmp = find_e1_e2(data, b1, b2);
	if (!tmp.x && !tmp.y)
		exit(EXIT_FAILURE);
	e1 = &data->edges[tmp.x];
	e2 = &data->edges[tmp.y];

	// do_log("First intersecting edges : ")
	if (is_edges_intersect(data, e1, e2) == e1)
	{
		draw_line(&(t_ivec2){e1->p1->x, e1->p1->y}, &(t_ivec2){e1->p2->x, e1->p2->y}, &data->screen, 0xff);
		draw_line(&(t_ivec2){e2->p1->x, e2->p1->y}, &(t_ivec2){e2->p2->x, e2->p2->y}, &data->screen, 0xff0000);
	}
	else
	{
		draw_line(&(t_ivec2){e2->p1->x, e2->p1->y}, &(t_ivec2){e2->p2->x, e2->p2->y}, &data->screen, 0xff);
		draw_line(&(t_ivec2){e1->p1->x, e1->p1->y}, &(t_ivec2){e1->p2->x, e1->p2->y}, &data->screen, 0xff0000);
	}
	return (0);
}

int8_t	compare_bunches(t_data *data, t_bunch *b1, t_bunch *b2)
{
	float	b1min;
	float	b1max;
	float	b2min;
	float	b2max;

	do_log("comparing bunch %ld and %ld\n", b1 - data->bunches, b2 - data->bunches);
	do_log("b1 has sector : %d, id_begin : %d, id_end : %d\n", b1->sector->id, b1->id_begin, b1->id_end);
	do_log("b2 has sector : %d, id_begin : %d, id_end : %d\n", b2->sector->id, b2->id_begin, b2->id_end);

	get_min_max(data, b1, &b1min, &b1max);
	get_min_max(data, b2, &b2min, &b2max);

	do_log("b1min : %f, b1max : %f\n", b1min, b1max);
	do_log("b2min : %f, b2max : %f\n", b2min, b2max);

	if (!interval_intersect(b1min, b1max, b2min, b2max))
	{
		do_log("b1 and b2 doesn't intersect with the normals\n");
		return (0);
	}
	else
	{
		return (handle_overlapping_bunches(data, b1, b2));
	}
}
