#include <editor.h>

/*
** Returns 1 if an element is touched, 0 else.
*/

static int8_t	loop_elems(int button, int x,int y, t_data *data)
{
	int		i;

	i = 0;
	if (button != 1)
		return (0);
	while (i < data->nb_elements)
	{
		if (data->elements[i].enabled)
		{
			if (is_in_polygon(x, y, data->elements[i]))
			{
				data->elements[i].on_click_func(data, i);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	mouse_hook(int button, int x,int y, t_data *data)
{
	printf("in mouse_hook.\n");
	printf("paramters : {button : %d, {%d, %d}}\n", button, x, y);
	if (x < 0 || y < 0 || x >= WIN_SIZE_X || y >= WIN_SIZE_Y)
		return (0);
	if (loop_elems(button, x, y, data))
		return (0);
	draw_edge(data, (t_ivec2){x, y});
	return (0);
}


/*

si on a clique


*/
