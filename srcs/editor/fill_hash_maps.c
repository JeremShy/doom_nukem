#include <editor.h>

uint16_t	*fill_hash_map_edges(t_data *data)
{
	uint16_t		*hash_map_edges;
	uint16_t		i;
	uint16_t		current;

	if (!(hash_map_edges = malloc(data->max_edge_id * sizeof(uint16_t))))
	{
		ft_putendl_fd("Memory error", 2);
		return (NULL);
	}
	i = 0;
	current = 0;
	while (i < data->max_edge_id)
	{
		if (data->edges[i].used)
		{
			hash_map_edges[i] = current;
			current++;
		}
		else
			hash_map_edges[i] = (uint16_t)-1u;
		i++;
	}
	return (hash_map_edges);
}

uint16_t	*fill_hash_map_points(t_data *data)
{
	uint16_t		*hash_map_points;
	uint16_t		i;
	uint16_t		current;

	if (!(hash_map_points = malloc(data->max_point_id * sizeof(uint16_t))))
	{
		ft_putendl_fd("Memory error", 2);
		return (NULL);
	}
	i = 0;
	current = 0;
	while (i < data->max_point_id)
	{
		if (data->used_point[i])
		{
			hash_map_points[i] = current;
			current++;
		}
		else
			hash_map_points[i] = (uint16_t)-1u;
		i++;
	}
	return (hash_map_points);
}

