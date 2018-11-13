#include <editor.h>

static uint8_t	ft_init(t_data *data)
{
	if (!(data->mlx.mlx_ptr = mlx_init()))
	{
		ft_putendl_fd("Error : Can't init mlx.", 2);
		return (0);
	}
	if (!(data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y, "Doom Nukem : Map editor")))
	{
		ft_putendl_fd("Error : Can't init window.", 2);
		return (0);
	}
	return (1);
}

int main()
{
	t_data	data;

	if (!ft_init(&data))
		return (1);
	printf("in editor\n");
	mlx_loop_hook(data.mlx.mlx_ptr, loop_hook, &data);
	mlx_mouse_hook(data.mlx.win_ptr, mouse_hook, &data);

	data.nb_params = 1;
	data.params[0] = (t_rectangle){1, 0, (t_vec2){0, 0}, (t_vec2){500, 500}, rectangle_on_click};

	mlx_loop(data.mlx.mlx_ptr);
	return (0);
}
