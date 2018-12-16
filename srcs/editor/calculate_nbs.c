#include <editor.h>

size_t	calculate_nb_edges(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < data->max_edge_id)
	{
		if (data->edges[i].used)
			ret++;
		i++;
	}
	return (ret);
}

size_t	calculate_nb_sectors(t_data *data)
{
	uint32_t	i;
	int			ret;

	i = 0;
	ret = 0;
	while (i < data->max_element_id)
	{
		if (data->elements[i].enabled)
			ret++;
		i++;
	}
	return (ret);
}

size_t	calculate_nb_points(t_data *data)
{
	int32_t	i;
	int			ret;

	i = 0;
	ret = 0;
	while (i < data->max_point_id)
	{
		if (data->used_point[i])
			ret++;
		i++;
	}
	return (ret);
}

size_t	calculate_nb_textures(t_data *data, int16_t *texture_hash_map)
{
	uint32_t	i;
	size_t	ret;

	i = 0;
	ret = 0;
	while (i < data->nbr_textures + IMG_START_TEXTURES)
	{
		if (texture_hash_map[i] != -1)
			ret++;
		i++;
	}
	return (ret);
}
