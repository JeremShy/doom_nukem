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

static uint8_t	ft_init(t_data *data, uint32_t w, uint32_t h)
{
	if (!(data->mlx.mlx_ptr = mlx_init()))
		ft_putendl_fd("Error: Can't init mlx.", 2);
	else if (!(data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y, "Doom Nukem : Map editor")))
		ft_putendl_fd("Error: Can't init window.", 2);
	else if (!create_image(data, IMG_BACKGROUND, w, h))
		return (0);
	else if (!create_image(data, IMG_DRAWING, 1061, h))
		return (0);
	else
	{
		data->input.id_current_element = -1;
		data->input.input_mode = DRAWING;
		return (1);
	}
	return (0);
}

int main()
{
	t_data			data;
	t_tga_header	header;
	uint32_t		*background;
	int i;

	ft_bzero(&data, sizeof(t_data));
	if (!(background = parse_tga("docs/background.tga", &header)))
		return (1);
	if (!ft_init(&data, header.image_spec.width, header.image_spec.width))
		return (2);
	i = 0;
	while (i < header.image_spec.width * header.image_spec.height)
	{
		put_pixel_to_image(&data.imgs[IMG_BACKGROUND], i % header.image_spec.width, header.image_spec.height - i / header.image_spec.width, invert_transparency(background[i]));
		i++;
	}
	printf("in editor\n");
	printf("data = %zu\nelement = %zu\npoint = %zu\nedge = %zu\npolygon = %zu\n\n", sizeof(data), sizeof(struct s_element), sizeof(struct s_ivec2), sizeof(struct s_edge), sizeof(struct s_polygon));
	mlx_loop_hook(data.mlx.mlx_ptr, loop_hook, &data);
	mlx_mouse_hook(data.mlx.win_ptr, mouse_hook, &data);
	mlx_key_hook(data.mlx.win_ptr, key_hook, &data);

	data.nb_elements = 1;

	printf("img ptr = %p\n", data.imgs[IMG_BACKGROUND].addr);
	// a1.x = 900, a1.y = 300, a2.x = 500, a2.y = 450, b1.x = 900, b1.y = 500, b2.x = 950, b2.y = 650

	// t_ivec2 p1 = {900, 300}; // rouge
	// t_ivec2 p2 = {500, 450}; // vert
	// t_ivec2 p3 = {900, 500}; // rose
	// t_ivec2 p4 = {950, 650}; // blanc

	// put_pixel_to_image(&data.imgs[0], p1.x, p1.y, get_color_code(255, 0, 0, 0));
	// put_pixel_to_image(&data.imgs[0], p2.x, p2.y, get_color_code(0, 255, 0, 0));
	// put_pixel_to_image(&data.imgs[0], p3.x, p3.y, get_color_code(255, 0, 255, 0));
	// put_pixel_to_image(&data.imgs[0], p4.x, p4.y, get_color_code(255, 255, 255, 0));
	// printf("%d\n", is_intersect(p1, p2, p3, p4).intersect);

	fill_img(&data.imgs[IMG_DRAWING], get_color_code(0, 0, 0, 255));

	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.imgs[IMG_BACKGROUND].ptr, 0, 0);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.imgs[IMG_DRAWING].ptr, 0, 0);


	mlx_loop(data.mlx.mlx_ptr);
	return (0);
}
