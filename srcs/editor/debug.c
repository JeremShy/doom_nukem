#include <editor.h>

void	liste_edges(t_data *data)
{
	int i;

	i = 0;
	printf("EDGE : -------------\n");
	while (i < data->max_edge_id)
	{
		if (data->edges[i].used)
			printf("edge[%u] * %u = {%u, %u}\n", i, data->edges[i].used, get_idpoint_from_addr(data->edges[i].p1, data), get_idpoint_from_addr(data->edges[i].p2, data));
		i++;
	}
}

void	liste_points(t_data *data)
{
	int i;

	i = 0;
	printf("POINT : -------------\n");
	printf("max_point_id : %d\n", data->max_point_id);
	printf("max_edge_id : %d\n", data->max_edge_id);
	while (i < data->max_point_id)
	{
		if (data->used_point[i])
			printf("point[%u] * %d = {%u, %u}\n", i, data->used_point[i], data->points[i].x, data->points[i].y);
		i++;
	}
}

