#include <game.h>

int mouse_hook(int button, int x, int y, t_data *data)
{
	printf("pos = {%f, %f}\n", data->player.pos.x, data->player.pos.y);
	return (1); 
}
