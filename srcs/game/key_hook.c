#include <game.h>

int	key_release(int keycode, t_data *data)
{
	data->key[keycode] = 0;
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESCAPE)
		close_hook(data);
	data->key[keycode] = 1;
	return (1);
}
