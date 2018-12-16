#include <game.h>

void	draw_all_edges(t_data *data)
{
	int	i;


	i = 0;
	while (i < data->nb_edges)
	{
		draw_line(&(t_ivec2){data->edges[i].p1->x, data->edges[i].p1->y}, &(t_ivec2){data->edges[i].p2->x, data->edges[i].p2->y}, &data->screen, get_color_code(255, 255, 255, 0));
		i++;
	}
}

int	loop(t_data *data)
{
	int		i;

	draw_all_edges(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->screen.ptr, 0, 0);

	return (0);
}
