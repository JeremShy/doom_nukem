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

	wall.id_p1 = edge->p1 - data->points;
	wall.id_p2 = edge->p2 - data->points;
	wall.angle_p1 = data->project_normal[wall.id_p1];
	if (data->project_normal[wall.id_p1] > M_PI - HALF_FOV)
		wall.angle_p1 += HALF_FOV - 2 * M_PI;
	else
		wall.angle_p1 += HALF_FOV;
	wall.angle_p2 = data->project_normal[wall.id_p2];
	if (data->project_normal[wall.id_p2] > M_PI - HALF_FOV)
		wall.angle_p2 += HALF_FOV - 2 * M_PI;
	else
		wall.angle_p2 += HALF_FOV;

	wall.dist_p1 = get_dist(edge->p1, &(t_vec2){data->player.pos.x, data->player.pos.y});
	wall.dist_p2 = get_dist(edge->p2, &(t_vec2){data->player.pos.x, data->player.pos.y});
			// printf("wall.angle_p1 = %f, wall.angle_p2 = %f\n", wall.angle_p1 , wall.angle_p2);
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
		fclamp(&begin, 0, FOV);
		fclamp(&end, 0, FOV);
		printf("edge = %d\n", edge->id);
		current = begin;
		while (current < end)
		{
			column = (current / FOV) * WIN_SIZE_X;
			current_dist = wall.dist_p1 + (wall.dist_p2 - wall.dist_p1) * (current - begin) / (end - begin);
			dir = ft_vec2_sub(*edge->p2, *edge->p1);
			dir = ft_vec2_get_normal(dir);
			1 - fabs(ft_vec2_dot(dir , const t_vec2 v))
			// current_dist = wall.dist_p1 *  (current - end) / (begin - end) + (wall.dist_p2 - wall.dist_p1) * (current - begin) / (end - begin);
			y = (WIN_SIZE_Y - (10 / current_dist * WIN_SIZE_Y)) / 2;
			while (y < (WIN_SIZE_Y + (10 / current_dist * WIN_SIZE_Y)) / 2)
			{
				put_pixel_to_image(&data->screen, column, y, get_color_code(255 - 255.0f * edge->id / data->nb_edges, 255.0f * edge->id / data->nb_edges, 255 - 255.0f * edge->id / data->nb_edges, 0));
				y++;
			}
			current += FOV / WIN_SIZE_X;
		}
	}
}
