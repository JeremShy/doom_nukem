#include <editor.h>

int16_t		*fill_hash_map_textures(t_data *data)
{
	int16_t		*hash_map_textures;
	uint32_t	i;
	int16_t		index_hash_map;

	hash_map_textures = malloc((data->nbr_textures + IMG_START_TEXTURES) * sizeof(int16_t));
	i = 0;
	while (i < data->nbr_textures + IMG_START_TEXTURES)
	{
		hash_map_textures[i] = -1;
		i++;
	}
	index_hash_map = 0;
	i = 0;
	while (i < data->max_edge_id)
	{
		if (data->edges[i].used)
		{
			if (data->edges[i].type == PORTAL)
			{
				if (hash_map_textures[data->edges[i].texture_up] == -1)
				{
					hash_map_textures[data->edges[i].texture_up] = index_hash_map;
					index_hash_map++;
				}
				if (hash_map_textures[data->edges[i].texture_down] == -1)
				{
					hash_map_textures[data->edges[i].texture_down] = index_hash_map;
					index_hash_map++;
				}
			}
			else
			{
				if (hash_map_textures[data->edges[i].texture_wall] == -1)
				{
					hash_map_textures[data->edges[i].texture_wall] = index_hash_map;
					index_hash_map++;
				}
			}
		}
		i++;
	}
	i = 0;
	while (i < data->max_element_id)
	{
		if (data->elements[i].enabled)
		{
			if (hash_map_textures[data->elements[i].texture_floor] == -1)
			{
				hash_map_textures[data->elements[i].texture_floor] = index_hash_map;
				index_hash_map++;
			}
			if (hash_map_textures[data->elements[i].texture_ceiling] == -1)
			{
				hash_map_textures[data->elements[i].texture_ceiling] = index_hash_map;
				index_hash_map++;
			}
		}
		i++;
	}
	i = 0;
	while ((uint16_t)i < data->nbr_textures + IMG_START_TEXTURES)
	{
		printf("hash_map_textures[%d] = %d\n", i, hash_map_textures[i]);
		i++;
	}
	return (hash_map_textures);

}

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

