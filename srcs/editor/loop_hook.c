#include <editor.h>

int	loop_hook(t_data *data)
{
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->imgs[IMG_BACKGROUND].ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->imgs[IMG_DRAWING].ptr, 0, 0);
	return (0);
}
