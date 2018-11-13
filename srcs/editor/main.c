#include <editor.h>

static uint8_t	create_image(t_data *data, int id, int w, int h)
{
	int	bpp;
	int	endian;
	int	size_line;

	t_img	*img;

	img = &data->imgs[id];
	if (id >= MAX_IMAGE)
		ft_putendl_fd("Error : Unknown id, please check MAX_IMAGE.", 2);
	else if (!(img->ptr = mlx_new_image(data->mlx.mlx_ptr, w, h)))
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

static uint8_t	ft_init(t_data *data)
{
	if (!(data->mlx.mlx_ptr = mlx_init()))
		ft_putendl_fd("Error: Can't init mlx.", 2);
	else if (!(data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y, "Doom Nukem : Map editor")))
		ft_putendl_fd("Error: Can't init window.", 2);
	else if (!create_image(data, IMAGE_TEST, 1600, 900))
		return (0);
	else
		return (1);
	return (0);
}

int main()
{
	t_data	data;

	if (!ft_init(&data))
		return (1);
	printf("in editor\n");
	mlx_loop_hook(data.mlx.mlx_ptr, loop_hook, &data);
	mlx_mouse_hook(data.mlx.win_ptr, mouse_hook, &data);

	data.nb_elements = 1;

	fill_img(&data.imgs[0], get_color_code(50, 50, 50, 0));

	t_ivec2 a1 = {1216, 483};
	t_ivec2 a2 = {1299, 608};
	t_ivec2 a3 = {1125, 682};

	printf("%d\n", 
		is_intersect(a1, a2, a2, a3));

	put_pixel_to_image(&data.imgs[0], a1.x, a1.y, get_color_code(0, 255, 0, 0));
	put_pixel_to_image(&data.imgs[0], a2.x, a2.y, get_color_code(255, 0, 255, 0));
	put_pixel_to_image(&data.imgs[0], a3.x, a3.y, get_color_code(255, 255, 255, 0));


	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.imgs[0].ptr, 0, 0);

	mlx_loop(data.mlx.mlx_ptr);
	return (0);
}
