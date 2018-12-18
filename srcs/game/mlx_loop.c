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

void	draw_fov_cone(t_data *data)
{
	t_vec3	fov_left;
	t_vec3	fov_right;
	t_vec2	p1;
	t_vec2	p2;

	fov_left = ft_vec3_scalar_mult(ft_vec3_rotate(data->player.dir, -45, (t_vec3){0, 0, -1}), 2000);
	fov_right = ft_vec3_scalar_mult(ft_vec3_rotate(data->player.dir, 45, (t_vec3){0, 0, -1}), 2000);
	p1 = (t_vec2){data->player.pos.x + fov_left.x, data->player.pos.y + fov_left.y};
	p2 = (t_vec2){data->player.pos.x + fov_right.x, data->player.pos.y + fov_right.y};
	draw_line(&(t_ivec2){data->player.pos.x, data->player.pos.y}, &(t_ivec2){p1.x, p1.y}, &data->screen, get_color_code(255, 0, 0, 0));
	draw_line(&(t_ivec2){data->player.pos.x, data->player.pos.y}, &(t_ivec2){p2.x, p2.y}, &data->screen, get_color_code(255, 0, 0, 0));
}

int	loop(t_data *data)
{
	int		i;

	fill_img(&data->screen, get_color_code(0, 0, 0, 0));

	fill_hash_pt_fov(data);
	flood_bunches(data);
	draw_all_visible_edges(data);
	draw_fov_cone(data);
	put_pixel_to_image(&data->screen, data->player.pos.x, data->player.pos.y, get_color_code(255, 255, 0, 0));
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->screen.ptr, 0, 0);

	// exit(0);

	return (0);
}
