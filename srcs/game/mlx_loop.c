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

void	draw_all_visible_edges(t_data *data)
{
	int	i;


	i = 0;
	while (i < data->nb_edges)
	{
		if (data->visible_edges[i])
			draw_line(&(t_ivec2){data->edges[i].p1->x, data->edges[i].p1->y}, &(t_ivec2){data->edges[i].p2->x, data->edges[i].p2->y}, &data->screen, get_color_code(255, 255, 255, 0));
		i++;
	}
}

int	loop(t_data *data)
{
	int		i;

	fill_hash_pt_fov(data);
	flood_bunches(data);
	draw_all_visible_edges(data);
	put_pixel_to_image(&data->screen, data->player.pos.x, data->player.pos.y, get_color_code(255, 255, 0, 0));
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->screen.ptr, 0, 0);

	// exit(0);

	return (0);
}
