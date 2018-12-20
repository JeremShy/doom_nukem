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
	{
		mlx_do_key_autorepeatoff(data->mlx.mlx_ptr);
		return (1);
	}
	return (0);
}

void	init_data(t_data *data)
{
	struct timeval tp;

	ft_mat4x4_set_rotation(data->mat_rot_dir_right, M_PI / 3, (t_vec3){0, 0, 1});
	ft_mat4x4_set_rotation(data->mat_rot_dir_left, -M_PI / 3, (t_vec3){0, 0, 1});
	data->player.dir = (t_vec3){0, -1, 0};
	gettimeofday(&tp, NULL);
	data->lasttime = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	ft_bzero(data->key, MAX_KEY + 1);
	data->need_update = 1;
}

int main(int ac, char **av)
{
	t_data	data;

	init_log("log.log");
	if (ac != 2)
		ft_putendl_fd("Usage: ./doom_nukems map", 2);
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
		// mlx_mouse_hook(data.mlx.win_ptr, &mouse_hook, &data);
		// mlx_loop_hook(data.mlx.mlx_ptr, loop_hook, &data);
		mlx_hook(data.mlx.win_ptr, 2, 0, key_press, &data);
		mlx_hook(data.mlx.win_ptr, 3, 0, key_release, &data);
		// mlx_hook(data.mlx.win_ptr, 4, 0, mouse_press, &data);
		// mlx_hook(data.mlx.win_ptr, 5, 0, mouse_release, &data);
		// mlx_hook(data.mlx.win_ptr, 6, 1l << 6, mouse_motion, &data);
		mlx_hook(data.mlx.win_ptr, 17, 3, close_hook, &data);
		mlx_loop_hook(data.mlx.mlx_ptr, loop, &data);
		init_data(&data);
		mlx_loop(data.mlx.mlx_ptr);
	}
	return (1);
}
