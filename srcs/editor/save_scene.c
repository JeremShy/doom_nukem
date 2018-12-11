#include <editor.h>
#include <file_format.h>

void		fill_sectors(t_data *data, uint8_t *addr)
{
	struct s_sector	*current_sec;
	struct s_wall	*current_wall;
	uint32_t	i;
	int	wall_i; // (LOL)

	i = 0;
	current_sec = (struct s_sector*)(addr + sizeof(struct s_header));
	while (i < data->nb_elements)
	{
		if (data->elements[i].enabled)
		{
			current_sec->id = i;
			current_sec->walls_number = data->elements[i].polygon.nb_points;
			// current_sec->normal_floor = calculate normale floor
			current_sec->height_floor = data->elements[i].height_floor;
			current_sec->texture_floor = data->elements[i].texture_floor;
			// current_sec->normal_ceiling = calculate normale ceiling
			current_sec->height_ceiling = data->elements[i].height_ceiling;
			current_sec->texture_ceiling = data->elements[i].texture_ceiling;
			current_sec->ambient_light = data->elements[i].light;
			// next_sector ?
			current_wall = (void*)current_sec + sizeof(struct s_sector);
			wall_i = 0;
			while (wall_i < data->elements[i].polygon.nb_points)
			{
				// fill walls id
			}


		}
		i++;
	}
}

uint8_t		save_scene(t_data *data)
{
	int		fd;
	uint8_t	*addr;
	size_t	file_size;
	struct s_header	*header;

	if ((fd = open(data->scene_name, O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1)
	{
		ft_putendl_fd("Error : Couldn't open scene file for writing", 2);
		exit (1);
	}
	file_size = calculate_file_size(data);
	printf("file size : %zu\n", file_size);
	if (!(addr = malloc(file_size)))
	{
		ft_putendl_fd("Memory error", 2);
		exit (2);
	}
	ft_bzero(addr, file_size);
	header = (struct s_header*)addr;
	header->size = (t_ivec2){MAP_SIZE, MAP_SIZE};
	// header->player pos
	header->sectors_number = calculate_nb_sectors(data);
	header->walls_number = calculate_nb_edges(data);
	header->texture_number = data->nbr_textures;
	// header->sprites_number;
	// header->objects_number;

	header->offset_walls = sizeof(struct s_header) + calculate_size_sectors(data);
	header->offset_texture = header->offset_walls + calculate_nb_edges(data) * sizeof(struct s_wall);
	header->offset_audio = header->offset_texture + calculate_size_textures(data);
	header->offset_objects = header->offset_audio + calculate_size_audios(data);

	write(fd, addr, file_size);
	exit (0);
}
