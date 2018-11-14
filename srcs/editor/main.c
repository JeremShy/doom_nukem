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
	{
		data->input.id_current_element = -1;
		return (1);
	}
	return (0);
}

int main()
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (!ft_init(&data))
		return (1);
	printf("in editor\n");
	mlx_loop_hook(data.mlx.mlx_ptr, loop_hook, &data);
	mlx_mouse_hook(data.mlx.win_ptr, mouse_hook, &data);
	mlx_key_hook(data.mlx.win_ptr, key_hook, &data);

	data.nb_elements = 1;

	fill_img(&data.imgs[IMAGE_TEST], get_color_code(50, 50, 50, 0));

	// {{261, 234}, {502, 233}} and {{337, 418}, {555, 73}}

	t_ivec2 p1 = {261, 234}; // rouge
	t_ivec2 p2 = {502, 233}; // vert
	t_ivec2 p3 = {337, 418}; // rose
	t_ivec2 p4 = {555, 73}; // blanc

	put_pixel_to_image(&data.imgs[0], p1.x, p1.y, get_color_code(255, 0, 0, 0));
	put_pixel_to_image(&data.imgs[0], p2.x, p2.y, get_color_code(0, 255, 0, 0));
	put_pixel_to_image(&data.imgs[0], p3.x, p3.y, get_color_code(255, 0, 255, 0));
	put_pixel_to_image(&data.imgs[0], p4.x, p4.y, get_color_code(255, 255, 255, 0));
	printf("%d\n", is_intersect(p2, p1, p3, p4));


	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.imgs[IMAGE_TEST].ptr, 0, 0);


	mlx_loop(data.mlx.mlx_ptr);
	return (0);
}
