#include <game.h>

uint8_t	can_see_edge(t_data *data, t_edge *edge)
{
	float	total_angle;
	float	angle1;
	float	angle2;

	angle1 = data->angle_dir_point[edge->p1 - data->points];
	angle2 = data->angle_dir_point[edge->p2 - data->points];
	if (angle1 > -HALF_FOV && angle1 < HALF_FOV)
	{
		printf("0\n");
		return (1);
	}
	if (angle2 > -HALF_FOV && angle2 < HALF_FOV)
	{
		printf("1\n");
		return (1);
	}
	if ((angle1 * angle2 > 0))
	{
		printf("2\n");
		return (0);
	}
	total_angle = fabs(angle1) + fabs(angle2);
	if (total_angle < M_PI)
	{
		printf("edge->p1 = {%f, %f} et edge->p2 = {%f, %f}\n", edge->p1->x, edge->p1->y, edge->p2->x, edge->p2->y);
		printf("angle1 = %f, angle2 = %f, total_angle = %f\n", angle1, angle2, total_angle);
		printf("3\n");
		return (1);
	}
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
