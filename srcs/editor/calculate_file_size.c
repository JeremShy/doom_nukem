#include <editor.h>
#include <file_format.h>

static size_t	calculate_size_objects(t_data *data)
{
	(void)data;
	return (0);
}

size_t			calculate_size_audios(t_data *data)
{
	(void)data;
	return (0);
}

size_t			calculate_size_textures(t_data *data, int16_t *hash_map_textures)
{
	uint16_t	i;
	size_t		ret;

	ret = 0;
	i = IMG_START_TEXTURES;
	while (i < data->nbr_textures + IMG_START_TEXTURES)
	{
		if (hash_map_textures[i] != -1)
			ret += sizeof(struct s_fftexture) + (data->imgs[i].original_w * data->imgs[i].original_h) * 4;
		i++;
	}
	return (ret);
}

size_t			calculate_size_points(t_data *data)
{
	uint16_t	i;
	uint16_t	ret;

	i = 0;
	ret = 0;
	while (i < data->max_point_id)
	{
		if (data->used_point[i])
			ret += sizeof(struct s_ivec2);
		i++;
	}
	return (ret);
}

size_t			calculate_size_sectors(t_data *data)
{
	uint16_t	i;
	size_t		ret;

	i = 0;
	ret = 0;
	while (i < data->max_element_id)
	{
		if (data->elements[i].enabled)
		{
			ret += sizeof(struct s_ffsector) + data->elements[i].polygon.nb_points * sizeof(uint16_t);
		}
		i++;
	}
	return (ret);
}

size_t			calculate_file_size(t_data *data, int16_t *hash_map_textures)
{
	size_t	ret;

	ret = sizeof(struct s_ffheader);
	ret += calculate_nb_sectors(data) * sizeof(struct s_ffsector);
	ret += calculate_size_points(data);
	ret += calculate_nb_edges(data) * sizeof(struct s_ffwall);
	ret += calculate_size_textures(data, hash_map_textures);
	ret += calculate_size_audios(data);
	ret += calculate_size_objects(data);
	return (ret);
}
