#include <game.h>


static struct s_ffsector	*parse_sector(t_data *data, struct s_ffsector *file_sector, uint16_t i)
{
	int			wall;
	uint16_t	*wall_ptr;

	data->sectors[i].id = i;
	data->sectors[i].nb_edges = file_sector->walls_number;
	data->sectors[i].texture_floor = file_sector->texture_floor;
	data->sectors[i].height_floor = file_sector->height_floor;
	data->sectors[i].normale_floor = file_sector->normal_floor;

	data->sectors[i].texture_ceiling = file_sector->texture_ceiling;
	data->sectors[i].height_ceiling = file_sector->height_ceiling;
	data->sectors[i].normale_ceiling = file_sector->normal_ceiling;

	wall_ptr = (uint16_t*)((void*)file_sector + (sizeof(struct s_ffsector)));
	wall = 0;
	while (wall < file_sector->walls_number)
	{
		data->sectors[i].edges[wall] = &data->edges[*wall_ptr];
		wall_ptr++;
		wall++;
	}
	return ((void*)wall_ptr);
}

uint8_t						parse_sectors(t_data *data, struct s_ffsector *file_sector)
{
	uint16_t	i;

	if (!(data->sectors = malloc(data->nb_sectors * sizeof(struct s_sector))))
		return (0);
	ft_bzero(data->sectors, data->nb_sectors * sizeof(struct s_sector));
	i = 0;
	while (i < data->nb_sectors)
	{
		file_sector = parse_sector(data, file_sector, i);
		i++;
	}
	return (1);
}
