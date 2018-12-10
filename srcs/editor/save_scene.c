#include <editor.h>
#include <file_format.h>

uint8_t		save_scene(t_data *data)
{
	int		fd;
	uint8_t	*file;
	size_t	file_size;
	struct s_header	*header;

	if ((fd = open(data->scene_name, O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1)
	{
		ft_putendl_fd("Error : Couldn't open scene file for writing", 2);
		exit (1);
	}
	file_size = calculate_file_size(data);
	printf("file size : %zu\n", file_size);
	if (!(file = malloc(file_size)))
	{
		ft_putendl_fd("Memory error", 2);
		exit (2);
	}
	ft_bzero(file, file_size);
	header = (struct s_header*)file;
	header->size = (t_ivec2){MAP_SIZE, MAP_SIZE};
	// header->player pos
	header->sectors_number = calculate_nb_sectors(data);
	header->walls_number = calculate_nb_edges(data);
	header->texture_number = data->nbr_textures;
	// header->sprites_number;
	// header->objects_number;

	header->offset_walls = calculate_nb_sectors(data) * sizeof(struct s_sector) + sizeof(struct s_header);
	header->offset_texture = header->offset_walls + calculate_nb_edges(data) * sizeof(struct s_wall);
	header->offset_audio = header->offset_texture + calculate_size_textures(data);
	header->offset_objects = header->offset_audio + calculate_size_audios(data);

	write(fd, file, file_size);
	exit (0);
}
