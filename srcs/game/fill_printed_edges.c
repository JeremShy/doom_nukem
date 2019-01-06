#include <game.h>

uint8_t	can_see_edge(t_data *data, t_edge *edge)
{
	float	total_angle;
	float	angle1;
	float	angle2;

	angle1 = data->angle_dir_point[edge->p1 - data->points];
	angle2 = data->angle_dir_point[edge->p2 - data->points];
	if (angle1 > -HALF_FOV && angle1 < HALF_FOV)
		return (1);
	if (angle2 > -HALF_FOV && angle2 < HALF_FOV)
		return (1);
	if ((angle1 * angle2 > 0))
		return (0);
	total_angle = fabs(angle1) + fabs(angle2);
	if (total_angle < M_PI)
		return (1);
	return (0);
}

void	fill_printed_edges(t_data *data)
{
	uint32_t	i;

	i = 0;
	data->nb_printed_edges = 0;
	while (i < data->nb_edges)
	{
		if (can_see_edge(data, &data->edges[i]))
		{
			data->printed_edges[data->nb_printed_edges] = &data->edges[i];
			(data->nb_printed_edges)++;
		}
		i++;
	}
}
