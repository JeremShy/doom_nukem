#include <editor.h>

void		string_put(t_data *data, int x, int y, int32_t string)
{
	char	*num_to_print;

	num_to_print = ft_itoa(string);
	mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, x, y, 0x1D1D1D, num_to_print);
	free(num_to_print);
}

static void	draw_strings(t_data *data)
{
	if (data->input.id_current_element == -1)
	{
		/*mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, SMALL_X_CEIL_VALUE_X, SMALL_X_CEIL_VALUE_Y, 0x1D1D1D, ft_itoa(data->input.angle_ceiling.x));
		mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, SMALL_Y_CEIL_VALUE_X, SMALL_Y_CEIL_VALUE_Y, 0x1D1D1D, ft_itoa(data->input.angle_ceiling.y));
		mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, CEIL_HEIGHT_VALUE_X, CEIL_HEIGHT_VALUE_Y, 0x1D1D1D, ft_itoa(data->input.height_ceiling));
		mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, SMALL_X_FLOOR_VALUE_X, SMALL_X_FLOOR_VALUE_Y, 0x1D1D1D, ft_itoa(data->input.angle_floor.x));
		mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, SMALL_Y_FLOOR_VALUE_X, SMALL_Y_FLOOR_VALUE_Y, 0x1D1D1D, ft_itoa(data->input.angle_floor.y));
		mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, FLOOR_HEIGHT_VALUE_X, FLOOR_HEIGHT_VALUE_Y, 0x1D1D1D, ft_itoa(data->input.height_floor));
		mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, LIGHT_VALUE_X, LIGHT_VALUE_Y, 0x1D1D1D, ft_itoa(data->input.light));*/
	}
	else if (data->input.mode == SELECTING)
	{
		string_put(data, SECTOR_NUM_X, SECTOR_NUM_Y, data->input.id_current_element);
		string_put(data, SMALL_X_CEIL_VALUE_X, SMALL_X_CEIL_VALUE_Y, data->elements[data->input.id_current_element].angle_ceiling.x);
		string_put(data, SMALL_Y_CEIL_VALUE_X, SMALL_Y_CEIL_VALUE_Y, data->elements[data->input.id_current_element].angle_ceiling.y);
		string_put(data, CEIL_HEIGHT_VALUE_X, CEIL_HEIGHT_VALUE_Y, data->elements[data->input.id_current_element].height_ceiling);
		string_put(data, SMALL_X_FLOOR_VALUE_X, SMALL_X_FLOOR_VALUE_Y, data->elements[data->input.id_current_element].angle_floor.x);
		string_put(data, SMALL_Y_FLOOR_VALUE_X, SMALL_Y_FLOOR_VALUE_Y, data->elements[data->input.id_current_element].angle_floor.y);
		string_put(data, FLOOR_HEIGHT_VALUE_X, FLOOR_HEIGHT_VALUE_Y, data->elements[data->input.id_current_element].height_floor);
		string_put(data, LIGHT_VALUE_X, LIGHT_VALUE_Y, data->elements[data->input.id_current_element].light);
	}
}

static void	draw_texture(t_data *data)
{
	if (data->input.id_current_element != -1 && data->input.mode == SELECTING)
	{
		// printf("%d\n", data->elements[data->input.id_current_element].texture_up);
		mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->imgs[data->elements[data->input.id_current_element].texture_up].ptr, UP_TEXTURE_X, UP_TEXTURE_Y);
		mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->imgs[data->elements[data->input.id_current_element].texture_down].ptr, DOWN_TEXTURE_X, DOWN_TEXTURE_Y);
		mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->imgs[data->elements[data->input.id_current_element].id_texture].ptr, WALL_TEXTURE_X, WALL_TEXTURE_Y);
		mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->imgs[data->elements[data->input.id_current_element].texture_ceiling].ptr, CEIL_TEXT_TEXTURE_X, CEIL_TEXT_TEXTURE_Y);
		mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->imgs[data->elements[data->input.id_current_element].texture_floor].ptr, FLOOR_TEXT_TEXTURE_X, FLOOR_TEXT_TEXTURE_Y);
	}
}


int			loop_hook(t_data *data)
{
	uint32_t i;
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	if (data->update_drawing)
	{
		fill_img(&data->imgs[IMG_DRAWING], get_color_code(0, 0, 0, 255));
		i = 0;
		while (i < data->nb_elements)
		{
			if (data->elements[i].enabled)
				draw_polygon(&data->elements[i].polygon, data);
			i++;
		}
		data->update_drawing = 0;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->imgs[IMG_BACKGROUND].ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->imgs[IMG_DRAWING].ptr, 0, 0);
	draw_texture(data);
	draw_strings(data);
	return (0);
}
