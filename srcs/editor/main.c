#include <editor.h>
#include <zlib.h>

uint8_t	create_image(t_data *data, int id, int w, int h)
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
		printf("Created image : %d\n", id);
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
	else if (!create_image(data, IMG_DRAWING, DRAWING_ZONE_WIDTH, WIN_SIZE_Y))
		return (0);
	else
	{
		data->input.id_current_element = -1;
		data->input.mode = DRAWING;
		data->max_element_id = 1;
		data->input.light = 100;
		data->input.texture_wall = IMG_START_TEXTURES;
		data->input.texture_up = IMG_START_TEXTURES;
		data->input.texture_down = IMG_START_TEXTURES;
		data->max_point_id = 0;
		data->max_edge_id = 0;
		data->update_drawing = 1;
		data->nbr_textures = 0;
		fill_img(&data->imgs[IMG_DRAWING], get_color_code(0, 0, 0, 255));
		return (1);
	}
	return (0);
}

static int		close_hook(t_data *data)
{
	(void)data;
	exit(EXIT_SUCCESS);
}
static uint8_t	ft_init_texture(t_data *data)
{
	if (!create_image_from_png(data, SQUARE_POINT, "docs/square.png", &(t_ivec2){21, 21}))
		return (0);
	return load_textures(data, ".png", "resources");
}

static void		create_first_sector(t_data *data)
{
	data->elements[0] = (t_element){0, 1, 1, 1, NULL, IMG_START_TEXTURES, {0, 0}, 0, IMG_START_TEXTURES, {0, 0}, 20, 100, (t_polygon){0, 1, {0}}};
	data->max_element_id = 1;
}

int main(int ac, char **av)
{
	t_data			data;

	if (ac != 2)
	{
		ft_printf("Usage: %s scene\n", av[0]);
		return (1);
	}
	ft_bzero(&data.used_point, sizeof(data.used_point));
	if (!ft_init(&data))
		return (1);
	if (!create_image_from_png(&data, IMG_BACKGROUND, "docs/new-background-5.png", NULL))
		return (2);
	if (!ft_init_texture(&data))
		return (3);
	data.scene_name = av[1];
	create_first_sector(&data);
	mlx_loop_hook(data.mlx.mlx_ptr, loop_hook, &data);
	mlx_hook(data.mlx.win_ptr, 2, 0, key_press, &data);
	mlx_hook(data.mlx.win_ptr, 3, 0, key_release, &data);
	mlx_hook(data.mlx.win_ptr, 4, 0, mouse_press, &data);
	mlx_hook(data.mlx.win_ptr, 5, 0, mouse_release, &data);
	mlx_hook(data.mlx.win_ptr, 6, 1l << 6, mouse_motion, &data);
	mlx_hook(data.mlx.win_ptr, 17, 3, close_hook, &data);
	mlx_loop(data.mlx.mlx_ptr);
	return (0);
}
