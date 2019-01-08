#include <game.h>

float		get_angle(t_vec2 dir, t_vec2 norm, t_vec2 point)
{
	float	rez;
	float	dot;
	int8_t	signe;

	signe = ft_vec2_dot(norm, point) > 0 ? 1 : -1;
	dot = ft_vec2_dot(dir, point);
	fclamp(&dot, -1, 1);
	rez = acosf(dot) * signe;
	return (rez);

}

uint8_t		project_points_on_normal(t_data *data)
{
	int		i;
	t_vec2	dir;
	t_vec2	norm;
	t_vec2	point;

	i = 0;
	norm = ft_vec2_get_normal((t_vec2){data->player.dir.x, data->player.dir.y});
	dir = (t_vec2){data->player.dir.x, data->player.dir.y};
	while (i < data->nb_points)
	{
		point = ft_vec2_sub(data->points[i], (t_vec2){data->player.pos.x, data->player.pos.y});
		ft_vec2_normalize(&point);
		data->project_normal[i] = get_angle(dir, norm, point);
		i++;
	}
	return (1);
}
