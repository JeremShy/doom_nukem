#include <game.h>

void	print_wall(t_data *data, t_edge *edge)
{
	struct	print_wall_data wall;
	float	begin;
	float	end;
	float	current;
	float	current_dist;
	int		y;
	int		column;
	t_vec2	dir;
	float	fov_y;

	printf("Printing wall with points : {%f, %f}, {%f, %f}\n", edge->p1->x, edge->p1->y, edge->p2->x, edge->p2->y);
	fov_y = FOV * (float)(WIN_SIZE_Y) / WIN_SIZE_X;
	wall.id_p1 = edge->p1 - data->points;
	wall.id_p2 = edge->p2 - data->points;
	wall.angle_p1 = data->project_normal[wall.id_p1];
	if (data->project_normal[wall.id_p1] > M_PI - HALF_FOV)
		wall.angle_p1 += HALF_FOV - 2 * M_PI;
	else
		 
	wall.angle_p2 = data->project_normal[wall.id_p2];
	if (data->project_normal[wall.id_p2] > M_PI - HALF_FOV)
		wall.angle_p2 += HALF_FOV - 2 * M_PI;
	else
		wall.angle_p2 += HALF_FOV;

	wall.dist_p1 = get_dist(edge->p1, &(t_vec2){data->player.pos.x, data->player.pos.y});
	wall.dist_p2 = get_dist(edge->p2, &(t_vec2){data->player.pos.x, data->player.pos.y});
	// printf("wall.angle_p1 = %f, wall.angle_p2 = %f\n", wall.angle_p1 , wall.angle_p2);

	printf("Wall angle : {%f, %f}\n", wall.angle_p1, wall.angle_p2);

	if (edge->type == WALL)
	{
		if (fmax(wall.angle_p1, wall.angle_p2) - fmin(wall.angle_p1, wall.angle_p2) >= M_PI)
		{
			begin = fmax(wall.angle_p1, wall.angle_p2);
			end = fmin(wall.angle_p1, wall.angle_p2) + 2 * M_PI;
		}
		else
		{
			begin = fmin(wall.angle_p1, wall.angle_p2);
			end = fmax(wall.angle_p1, wall.angle_p2);
		}

		printf("begin : %f\n", begin);
		printf("end : %f\n", end);

		t_vec2	ap = ft_vec2_sub((t_vec2){data->player.pos.x, data->player.pos.y}, *edge->p1);
		t_vec2	ab = ft_vec2_sub(*edge->p2, *edge->p1);

		float	beta = fabsf(ft_vec2_get_angle(ap, ab));
		printf("beta 1 = %f\n", beta / M_PI * 180);
		beta = fabsf(ft_vec2_get_angle(ab, ap));
		printf("beta 2 = %f\n", beta / M_PI * 180);
		float	gamma = M_PI - fabsf(begin) - beta;

		float pc = sinf(beta) * ft_vec2_get_norme(ap) / sinf(gamma);

		printf("gammma = %f\n", gamma / M_PI * 180);
		printf("beta = %f\n", beta / M_PI * 180);
		printf("begin = %f\n", begin / M_PI * 180);
		float alpha = end - M_PI / 2;

		t_vec2	bp = ft_vec2_sub((t_vec2){data->player.pos.x, data->player.pos.y}, *edge->p2);
		t_vec2	ba = ft_vec2_sub(*edge->p1, *edge->p2);

		beta = fabsf(ft_vec2_get_angle(bp, ba));

		gamma = M_PI - alpha - beta;

		float pd = sinf(beta) * ft_vec2_get_norme(bp) / sinf(gamma);

		fclamp(&begin, 0, FOV);
		fclamp(&end, 0, FOV);
		printf("edge = %d\n", edge->id);
		printf("pc = %f, pd = %f\n", pc , pd);
		current = begin;

		float	dist = 20 / (tanf(fov_y / 2));

		while (current < end)
		{
			column = (current / FOV) * WIN_SIZE_X;
			current_dist = pc + fabs(pd - pc) * ((current - begin) / (end - begin));
			// current_dist = pc + fabs(pd - pc) * (current - begin) / (end - begin);
			// printf("current_dist = %f\n", current_dist);
			// current_dist = pc;
			// current_dist = wall.dist_p1 + (wall.dist_p2 - wall.dist_p1) * (current - begin) / (end - begin);
			// y = (WIN_SIZE_Y - (10 / current_dist * WIN_SIZE_Y)) / 2;
			int		cm;
			// cm = WIN_SIZE_Y / 2 * current_dist / 10;
			// y = WIN_SIZE_Y / 2 - (cm - 1) / cm * WIN_SIZE_Y;
			y = (WIN_SIZE_Y - (current_dist * WIN_SIZE_Y)) / 2;
			// printf("y = %d\n", y);

			float	hauteur_de_tout = 20 * current_dist / dist;

			printf("current = %f\n", current);
			float	h = 20 / hauteur_de_tout * WIN_SIZE_Y;
			float	y_begin;
			float	y_end;
			float	y;

			y_begin = WIN_SIZE_Y / 2 - h;
			y_end = WIN_SIZE_Y / 2 + h;

			y = y_begin;

			while (y < y_end)
			{
				put_pixel_to_image(&data->screen, column, y, get_color_code(255 - 255.0f * edge->id / data->nb_edges, 255.0f * edge->id / data->nb_edges, 255 - 255.0f * edge->id / data->nb_edges, 0));
				y++;
			}
			current += FOV / WIN_SIZE_X;
		}
	}
}
