#include <game.h>

uint8_t		project_points_on_normal(t_data *data)
{
	int		i;
	t_vec2	norm;

	i = 0;
	norm = ft_vec2_get_normal((t_vec2){data->player.dir.x, data->player.dir.y});
	while (i < data->nb_points)
	{
		if (data->used_points[i])
		{
			data->project_normal[i] = ft_vec2_dot(norm, data->points[i]);
		}
		else
			data->project_normal[i] = -1u;
		i++;
	}
	return (1);
}
