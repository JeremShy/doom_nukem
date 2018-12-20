#include <game.h>

uint8_t	interval_intersect(float a1, float a2, float b1, float b2)
{
	float		mini;
	float		maxi;

	mini = fmin(a1, a2);
	maxi = fmax(a1, a2);
	if (b1 <= mini && b2 <= mini)
		return (0);
	if (b1 >= maxi && b2 >= maxi)
		return (0);
	return (1);
}

void	get_min_max(t_data *data, t_bunch *bunch, float *min, float *max)
{
	int			i;
	t_sector	*sec;
	uint16_t	p1_float;
	uint16_t	p2_float;

	sec = bunch->sector;
	i = bunch->id_begin;
	*min = data->project_normal[sec->edges[bunch->id_begin]->p1 - data->points];
	*max = data->project_normal[sec->edges[bunch->id_begin]->p1 - data->points];
	while (i % sec->nb_edges <= bunch->id_begin)
	{
		p1_float = data->project_normal[sec->edges[i % sec->nb_edges]->p1 - data->points];
		p2_float = data->project_normal[sec->edges[i % sec->nb_edges]->p2 - data->points];
		if (p1_float < *min)
			*min = p1_float;
		if (p1_float > *max)
			*max = p1_float;
		if (p2_float < *min)
			*min = p2_float;
		if (p2_float > *max)
			*max = p2_float;
		i++;
	}
}

/*
** e1 and e2 are the two first overlapping walls
*/
t_ivec2	find_e1_e2(t_data *data, t_bunch *b1, t_bunch *b2)
{
	int i;
	int j;
	int nb;

	i = b1->id_begin;
	while (i != b1->id_end + 1)
	{
		while ((j + b2->id_begin) % b2->sector->nb_edges < b2->id_end)
		{
			if (interval_intersect(b1->sector->edges[i], float a2, float b1, float b2))
			j++;
		}
		i = (i + 1) % b1->sector->nb_edges;
	}
	return ((t_ivec2){0, 0});
}

int8_t	handle_overlapping_bunches(t_data *data, t_bunch *b1, t_bunch *b2)
{
	t_edge	*e1;
	t_edge	*e2;

	return (0);
}

int8_t	compare_bunches(t_data *data, t_bunch *b1, t_bunch *b2)
{
	float	b1min;
	float	b1max;
	float	b2min;
	float	b2max;

	get_min_max(data, b1, &b1min, &b1max);
	get_min_max(data, b2, &b2min, &b2max);
	if (!interval_intersect(b1min, b1max, b2min, b2max))
		return (0);
	else
		return (handle_overlapping_bunches(data, b1, b2));
}
