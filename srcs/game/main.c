#include <game.h>

uint8_t	create_image(t_data *data, int w, int h)
{
	int	bpp;
	int	endian;
	int	size_line;

	t_img	*img;

	img = &data->screen;
	if (!(img->ptr = mlx_new_image(data->mlx.mlx_ptr, w, h)))
		ft_putendl_fd("Error: Couldn't create new image.", 2);
	else if (!(img->addr = (void*)mlx_get_data_addr(img->ptr, &bpp, &size_line, &endian)))
		ft_putendl_fd("Error : Couldn't get data_addr of the new image.", 2);
	else if (bpp != 32 || endian != 0 || size_line != w * 4)
		ft_putendl_fd("Error : Unexpected bpp and endian.", 2);
	else
	{
		img->h = h;
		img->w = w;
		return (1);
	}
	return (0);
}

static uint8_t	ft_mlx_init(t_data *data)
{
	if (!(data->mlx.mlx_ptr = mlx_init()))
		ft_putendl_fd("Error: Can't init mlx.", 2);
	else if (!(data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y, "Doom Nukem : Map editor")))
		ft_putendl_fd("Error: Can't init window.", 2);
	else if (!create_image(data, WIN_SIZE_X, WIN_SIZE_Y))
		ft_putendl_fd("Error: Can't create image.", 2);
	else
		return (1);
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		ft_putendl_fd("Usage: ./doom_nukem map", 2);
	else if (!parse_map(&data, av[1]))
		ft_putendl_fd("Parse error.", 2);
	else if (!ft_mlx_init(&data))
		ft_putendl_fd("Init error.", 2);
	else if (!(data.angle_dir_point = malloc(sizeof(float) * data.nb_points)))
		ft_putendl_fd("Memory error.", 2);
	else if (!(data.visible_edges = malloc(sizeof(uint8_t) * data.nb_edges)))
		ft_putendl_fd("Memory error.", 2);
	else
	{
		data.player.dir = (t_vec3){0, -1, 0};
		mlx_mouse_hook(data.mlx.win_ptr, &mouse_hook, &data);
		mlx_loop_hook(data.mlx.mlx_ptr, loop, &data);

		printf("%f\n", radians_to_degrees(get_angle_player_point(&data.player, &(t_vec2){350, 600})));
		// exit(0);

		mlx_loop(data.mlx.mlx_ptr);
	}
	return (1);
}
