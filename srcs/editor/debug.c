#include <editor.h>

void	liste_edges(t_data *data)
{
	int i;

	i = 0;
	printf("EDGE : -------------\n");
	while (i < MAX_POINTS_NBR)
	{
		if (data->edges[i].used)
			printf("edge[%u] = {%u, %u}\n", i, get_idpoint_from_addr(data->edges[i].p1, data), get_idpoint_from_addr(data->edges[i].p2, data));
		i++;
	}
}

void	liste_points(t_data *data)
{
	int i;

	i = 0;
	printf("POINT : -------------\n");
	while (i < MAX_POINTS_NBR)
	{
		if (data->used_point[i])
			printf("point[%u] * %d = {%u, %u}\n", i, data->used_point[i], data->points[i].x, data->points[i].y);
		i++;
	}
}

