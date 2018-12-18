#include <game.h>

int mouse_hook(int button, int x, int y, t_data *data)
{
	printf("pos = {%f, %f}\n", data->player.pos.x, data->player.pos.y);
	return (1); 
}

int key_hook(int button, int x, int y, t_data *data)
{
	printf("pos joueur = {%f, %f}\n", data->player.pos.x, data->player.pos.y);
	return (1); 
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
	{
		data->player.dir = ft_vec4_to_vec3(ft_mat4x4_mult_with_vec4(data->mat_rot_dir_left, ft_vec3_to_vec4(data->player.dir)));
	}
	else if (keycode == KEY_RIGHT)
	{
		data->player.dir = ft_vec4_to_vec3(ft_mat4x4_mult_with_vec4(data->mat_rot_dir_right, ft_vec3_to_vec4(data->player.dir)));
	}
	return (1);
}
