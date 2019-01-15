#include <game.h>

// TODO : Virer les matrices de rotation

void	handle_key_events(t_data *data)
{
	t_vec2	speed;
	t_vec2	dir_front;
	t_vec2	dir_side;

	if (data->key[KEY_LEFT])
	{
		ft_mat4x4_set_rotation(data->mat_rot_dir_left, -M_PI / 3 * (SPEED / 1000.f) * data->deltatime, (t_vec3){0, 0, 1});
		data->player.dir = ft_vec4_to_vec3(ft_mat4x4_mult_with_vec4(data->mat_rot_dir_left, ft_vec3_to_vec4(data->player.dir)));
		data->need_update = 1;
	}
	if (data->key[KEY_RIGHT])
	{
		ft_mat4x4_set_rotation(data->mat_rot_dir_right, M_PI / 3 * (SPEED / 1000.f) * data->deltatime, (t_vec3){0, 0, 1});
		data->player.dir = ft_vec4_to_vec3(ft_mat4x4_mult_with_vec4(data->mat_rot_dir_right, ft_vec3_to_vec4(data->player.dir)));
		data->need_update = 1;
	}
	dir_front.x = 0;
	dir_front.y = 0;
	dir_side.x = 0;
	dir_side.y = 0;
	if (data->key[KEY_W] || data->key[KEY_S])
	{
		dir_front = (t_vec2){data->player.dir.x, data->player.dir.y};

		if (data->key[KEY_S])
		{
			dir_front.x *= -1;
			dir_front.y *= -1;
		}
	}
	if (data->key[KEY_A] || data->key[KEY_D])
	{
		dir_side = ft_vec2_get_normal((t_vec2){data->player.dir.x, data->player.dir.y});
		if (data->key[KEY_A])
		{
			dir_side.x *= -1;
			dir_side.y *= -1;
		}
	}
	speed.x = (dir_front.x + dir_side.x) * (SPEED / 1000.f) * data->deltatime;
	speed.y = (dir_front.y + dir_side.y) * (SPEED / 1000.f) * data->deltatime;
	if (speed.x != 0 || speed.y != 0)
	{
		data->player.pos = ft_vec3_add(data->player.pos, (t_vec3){speed.x, speed.y, 0});
		data->need_update = 1;
	}
}
