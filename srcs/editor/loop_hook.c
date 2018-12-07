#include <editor.h>

static void	draw_strings(t_data *data)
{
	mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, CEIL_ORI_Y_VALUE_SX, CEIL_ORI_Y_VALUE_SY, 0x1D1D1D, ft_itoa(data->input.ceiling_angle_y));
	mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, CEIL_ORI_X_VALUE_SX, CEIL_ORI_X_VALUE_SY, 0x1D1D1D, ft_itoa(data->input.ceiling_angle_x));
	mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, CEIL_HEIGHT_VALUE_SX, CEIL_HEIGHT_VALUE_SY, 0x1D1D1D, ft_itoa(data->input.ceiling_height));
	mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, FLOOR_ORI_Y_VALUE_SX, FLOOR_ORI_Y_VALUE_SY, 0x1D1D1D, ft_itoa(data->input.floor_angle_y));
	mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, FLOOR_ORI_X_VALUE_SX, FLOOR_ORI_X_VALUE_SY, 0x1D1D1D, ft_itoa(data->input.floor_angle_x));
	mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, FLOOR_HEIGHT_VALUE_SX, FLOOR_HEIGHT_VALUE_SY, 0x1D1D1D, ft_itoa(data->input.floor_height));
	mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, LIGHT_VALUE_SX, LIGHT_VALUE_SY, 0x1D1D1D, ft_itoa(data->input.light));
}

int			loop_hook(t_data *data)
{
	uint32_t i;
	// mlx_clear_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	// if (data->update_drawing)
	// {
	// 	fill_img(&data->imgs[IMG_DRAWING], get_color_code(0, 0, 0, 255));
	// 	i = 0;
	// 	while (i < data->nb_elements)
	// 	{
	// 		if (data->elements[i].enabled)
	// 			draw_polygon(&data->elements[i].polygon, data);
	// 		i++;
	// 	}
	// 	data->update_drawing = 0;
	// }
	// mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->imgs[IMG_BACKGROUND].ptr, 0, 0);
	// mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->imgs[IMG_DRAWING].ptr, 0, 0);
	// draw_strings(data);
	return (0);
}
