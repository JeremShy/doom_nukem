#include <editor.h>

void	rectangle_on_click(t_data *data, int id)
{
	printf("in rectangle_on_click.\n");
}

int8_t	in_rectangle(int x, int y, t_rectangle rect)
{
	if (x > rect.bottom_left.x && x < rect.up_right.x
		&& y > rect.bottom_left.y && y < rect.up_right.y)
	{
		return (1);
	}
	return (0);
}
