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
		data->nb_elements = 1;
		data->input.light = 100;
		data->input.texture_wall = 1;
		data->input.texture_up = 1;
		data->input.texture_down = 1;
		data->update_drawing = 1;
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
	if (!create_image_from_tga(data, TEXTURE_1, "docs/texture-bleu.tga", NULL))
		return (1);
	if (!create_image_from_tga(data, TEXTURE_2, "docs/texture-rouge.tga", NULL))
		return (1);
	if (!create_image_from_tga(data, TEXTURE_3, "docs/texture-jaune.tga", NULL))
		return (1);
	if (!create_image_from_tga(data, TEXTURE_4, "docs/moche.tga", NULL))
		return (1);
	return (0);
}

int main(int ac, char **av)
{
	t_data			data;

	(void)av;
	(void)ac;
	ft_bzero(&data.used_point, sizeof(data.used_point));
	// ft_memset(&data, sizeof(t_data), '1');
	if (!ft_init(&data))
		return (1);
	if (!create_image_from_png(&data, IMG_BACKGROUND, "docs/new-background-2.png", NULL))
		return (2);
	if (ft_init_texture(&data))
		return (3);
	ft_init_texture(&data);
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
