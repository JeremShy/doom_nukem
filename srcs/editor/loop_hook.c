#include <editor.h>
/*
void	print_strings(t_data *data)
{
	
}*/

int		loop_hook(t_data *data)
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
	}
	data->update_drawing = 0;
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->imgs[IMG_BACKGROUND].ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->imgs[IMG_DRAWING].ptr, 0, 0);
	/*draw_strings(data);*/
	return (0);
}
