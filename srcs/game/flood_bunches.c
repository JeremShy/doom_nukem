#include <game.h>

uint8_t	can_see_edge(t_data *data, t_edge *edge)
{
	float	total_angle;
	float	angle1;
	float	angle2;

	angle1 = data->angle_dir_point[edge->p1 - data->points];
	angle2 = data->angle_dir_point[edge->p2 - data->points];
	// printf("angle1 = %f et angle2 = %f\n", angle1, angle2);
	if (angle1 > -HALF_FOV && angle1 < HALF_FOV)
		return (1);
	if (angle2 > -HALF_FOV && angle2 < HALF_FOV)
		return (1);
	if ((angle1 * angle2 > 0))
	{
		// printf("I dont see the angles : %f - %f\n", radians_to_degrees(angle1), radians_to_degrees(angle2));
		return (0);
	}
	total_angle = fabs(angle1) + fabs(angle2);
	if (total_angle < M_PI)
		return (1);
	printf("I dont see the angles : %f - %f\n", radians_to_degrees(angle1), radians_to_degrees(angle2));
	return (0);
}

void	flood_bunches(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nb_edges)
	{
		data->visible_edges[i] = can_see_edge(data, &data->edges[i]);
		i++;
	}
}
