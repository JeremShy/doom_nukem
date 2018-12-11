#include <editor.h>

void	print_click(t_data *data, uint16_t id)
{
	(void)data;
	printf("clicked element  : %u\n", id);
}

uint8_t check_point(t_data *data, const t_ivec2 *point, t_ivec2 *exept)
{
	float			dist;

	if (exept)
		get_nearest_edge_except(point, data, &dist, exept);
	else
		get_nearest_edge(point, data, &dist);
	if (dist != -1 && dist < 10)
		return (0);
	return (1);
}

uint8_t check_segment(t_data *data, const t_ivec2 *new_point, const t_ivec2 *last_point)
{
	uint32_t		j;

	j = 0;
	while (j < data->nb_elements)
	{
		if (data->elements[j].enabled)
			if (nb_intersec_in_poly(&data->elements[j].polygon, new_point, last_point))
				return (0);
		j++;
	}
	return (1);
}
