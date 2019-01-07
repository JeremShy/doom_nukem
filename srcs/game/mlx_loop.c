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

void	draw_sector(t_data *data, int i)
{
	uint32_t	color;
	int j = 0;

	while (j < data->sectors[i].nb_edges)
	{
		if (data->visible_edges[data->sectors[i].edges[j]->id])
			color = get_color_code(0, 0xff, 0, 0);
		else
			color = get_color_code(0, 0, 0, 0);
		draw_line(&(t_ivec2){data->sectors[i].edges[j]->p1->x, data->sectors[i].edges[j]->p1->y}, &(t_ivec2){data->sectors[i].edges[j]->p2->x, data->sectors[i].edges[j]->p2->y}, &data->screen, color);
		j++;
	}
}

t_edge	*find_next_to_print(t_data *data)
{
	uint32_t	i;
	t_edge		*closest;
	uint32_t	iclosest;
	t_edge		*cur;

	closest = NULL;
	iclosest = 1;
	i = 0;

	while (i < data->nb_printed_edges)
	{
		cur = data->printed_edges[i];
		if (cur != NULL)
		{
			if (closest == NULL || (cmp_edges_order(data, cur, closest) < 0 && cmp_edges_order(data, closest, cur) > 0))
			{
				if (!closest)
					do_log("initialisizing at %d\n", cur->id);
				else
					do_log("Changing from %d to %d\n", closest->id, cur->id);
				iclosest = i;
				closest = cur;
				// i = 0;
			}
		}
		i++;
	}
	if (closest)
	{
		do_log("Electing : %d\n", closest->id);
		data->printed_edges[iclosest] = NULL;
	}
	return (closest);
}

void	draw_edges(t_data *data)
{
	uint32_t	i;
	t_edge		*to_print;
	uint32_t	color;
	t_vec2		p;

	// color = get_color_code(0, 0, 255, 0);
	color = 0xff;
	fill_printed_edges(data);
	i = 0;
	printf("Nb printed edges : %d\n", data->nb_printed_edges);
	while (i < data->nb_printed_edges)
	{
		if (!(to_print = find_next_to_print(data)))
		{
			printf("Error : to_print is null\n");
			exit(0);
		}
		// draw_line(&(t_ivec2){to_print->p1->x, to_print->p1->y}, &(t_ivec2){to_print->p2->x, to_print->p2->y}, &data->screen, color);
		draw_line(&(t_ivec2){to_print->p1->x, to_print->p1->y}, &(t_ivec2){to_print->p2->x, to_print->p2->y}, &data->screen, get_color_code(color, color, color, 0));
		// if (color == get_color_code(0, 0, 255, 0))
			// color = get_color_code(255, 0, 0, 0);
		// else
			// color = 0;
		color -= 0xff / data->nb_printed_edges;

		p = (t_vec2){(to_print->p1->x + to_print->p2->x) / 2, (to_print->p1->y + to_print->p2->y) / 2};
		char *str;
		asprintf(&str, "%hu", to_print->id);
		mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, p.x - 8, p.y - 8, get_color_code(0, 255, 0, 0), str);

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
	struct timeval	tp;
	static int		fps = 0;
	static int		time = 0;
	// t_mat4x4		rez;

	gettimeofday(&tp, NULL);
	data->deltatime = (tp.tv_sec * 1000 + tp.tv_usec / 1000) - data->lasttime;
	data->lasttime = (tp.tv_sec * 1000 + tp.tv_usec / 1000);
	handle_key_events(data);
	if (data->need_update)
	{
		do_log("New image --------------------------------------------\n-----------------------\n");
		// ft_mat4x4_set_look_at(data->look_at, data->player.pos, data->player.dir, (t_vec3){0, 0, 1});
		mlx_clear_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
		// ft_mat4x4_mult(rez, data->look_at, data->projection);
		fill_img(&data->screen, get_color_code(0, 0, 0, 255));
		fill_hash_pt_fov(data);
		// check_projection_point(data);
		project_points_on_normal(data);

		draw_edges(data);

		draw_fov_cone(data);
	}
	put_pixel_to_image(&data->screen, data->player.pos.x, data->player.pos.y, get_color_code(255, 255, 0, 0));
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->screen.ptr, 0, 0);
	fps++;
	time += data->deltatime;
	data->need_update = 0;
	if (time > 1000)
	{
		time -= 1000;
		printf("fps = %d\n", fps);
		fps = 0;
	}
	return (0);
}

