#include <game.h>

float			get_angle_player_point(t_player *player, t_vec2 *point)
{
	t_vec2	dir_point;
	t_vec2	normal;
	float	angle;
	float	dot;
	float	dot_normal;

	printf("player : \n");
	ft_vec2_print((t_vec2){player->pos.x, player->pos.y});
	printf("point : \n");
	ft_vec2_print(*point);

	dir_point = ft_vec2_sub(*point, (t_vec2){player->pos.x, player->pos.y});

	printf("result : \n");
	ft_vec2_print(dir_point);

	ft_vec2_normalize(&dir_point);
	normal = ft_vec2_get_normal((t_vec2){player->dir.x, player->dir.y});

	printf("normalized : \n");
	ft_vec2_print(dir_point);

	dot = ft_vec2_dot(dir_point, (t_vec2){player->dir.x, player->dir.y});
	dot_normal = ft_vec2_dot(dir_point, normal);

	angle = acos(dot) * (dot_normal > 0 ? 1 : -1);
	return (angle);
}

void			fill_hash_pt_fov(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nb_points)
	{
		data->angle_dir_point[i] = get_angle_player_point(&data->player, &data->points[i]);
		i++;
	}
}
