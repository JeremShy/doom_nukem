#include <game.h>

int mouse_hook(int button, int x, int y, t_data *data)
{
	printf("pos = {%d, %d}\n", x, y);
	return (1); 
}
