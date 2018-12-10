#include <editor.h>
#include <file_format.h>

static size_t	calculate_size_objects(t_data *data)
{
	(void)data;
	return (0);
}

size_t	calculate_size_audios(t_data *data)
{
	(void)data;
	return (0);
}

size_t			calculate_size_textures(t_data *data)
{
	uint16_t	i;
	size_t		ret;

	ret = 0;
	i = IMG_START_TEXTURES;
	while (i < data->nbr_textures)
	{
		ret += sizeof(struct s_texture) + (data->imgs[i].w * data->imgs[i].h) * 4 * sizeof(uint8_t);
		i++;
	}
	return (ret);
}

size_t			calculate_file_size(t_data *data)
{
	size_t	ret;

	ret = sizeof(struct s_header);
	ret += calculate_nb_sectors(data) * sizeof(struct s_sector);
	ret += calculate_nb_edges(data) * sizeof(struct s_wall);
	ret += calculate_size_textures(data);
	ret += calculate_size_audios(data);
	ret += calculate_size_objects(data);
	return (ret);
}
