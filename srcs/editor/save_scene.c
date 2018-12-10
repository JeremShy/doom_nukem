#include <editor.h>
#include <file_format.h>

uint8_t		save_scene(t_data *data)
{
	int		fd;
	uint8_t	*file;
	size_t	file_size;

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
	
	exit (0);
}
