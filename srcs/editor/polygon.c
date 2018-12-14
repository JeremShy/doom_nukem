#include <editor.h>

uint8_t check_all_points(t_data *data, t_ivec2 *exept)
{
	int i;
	float	dist;

	i = 0;
	while (i < data->max_point_id)
	{
		if (data->used_point[i])
			get_nearest_edge_except(&data->points[i], data, &dist, &data->points[i]);
		if (dist != -1 && dist < 20)
			return (0);
		i++;
	}
	return (1);
}

uint8_t check_point(t_data *data, const t_ivec2 *point, t_ivec2 *exept)
{
	float	dist;

	if (exept)
		get_nearest_edge_except(point, data, &dist, exept);
	else
		get_nearest_edge(point, data, &dist);
	if (dist != -1 && dist < 20)
		return (0);
	return (1);
}

uint8_t check_segment(t_data *data, const t_ivec2 *new_point, const t_ivec2 *last_point)
{
	uint32_t		j;

	j = 0;
	while (j < data->max_element_id)
	{
		if (data->elements[j].enabled)
			if (nb_intersec_in_poly(&data->elements[j].polygon, new_point, last_point))
				return (0);
		j++;
	}
	return (1);
}
