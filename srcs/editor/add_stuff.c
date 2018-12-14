#include <editor.h>

t_ivec2	*add_points(t_data *data, const t_ivec2 *new_point)
{
	int32_t i;

	i = 0;
	while (i < MAX_POINTS_NBR)
	{
		if (!data->used_point[i])
		{
			data->points[i] = *new_point;
			data->used_point[i] = 1;
			if (i == data->max_point_id)
				data->max_point_id++;
			return (&data->points[i]);
		}
		i++;
	}
	ft_putendl_fd("Error : No space left on Points", 2);
	exit(EXIT_FAILURE);
}

t_edge	*add_edge(t_data *data, const t_edge new_edge)
{
	int32_t i;

	i = 0;
	while (i < MAX_POINTS_NBR)
	{
		if (!data->edges[i].used)
		{
			data->edges[i] = new_edge; // /!\ Copies everything from new edge to data->edges[i]
			if (i == data->max_edge_id)
				data->max_edge_id++;
			return (&data->edges[i]);
		}
		i++;
	}
	ft_putendl_fd("Error : No space left on Edge", 2);
	exit(EXIT_FAILURE);
}

