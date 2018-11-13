#include <editor.h>

static void	loop_rectangles(int button, int x,int y, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_params)
	{
		if (data->params[i].enabled)
		{
			if (is_in_polygon(x, y, data->params[i]))
			{
				data->params[i].func(data, i);
			}
		}
		i++;
	}
}

int	mouse_hook(int button, int x,int y, t_data *data)
{
	printf("in mouse_hook.\n");
	printf("paramters : {button : %d, {%d, %d}}\n", button, x, y);
	loop_rectangles(button, x, y, data);
	return (0);
}


/*

si on a clique


*/
