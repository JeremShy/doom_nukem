#include <editor.h>

/*
** Returns 1 if an element is touched, 0 else.
*/

static int8_t	loop_elems(int button, int x,int y, t_data *data)
{
	uint32_t		i;

	i = 0;
	if (button != 1)
		return (0);
	while (i < data->nb_elements)
	{
		if (data->elements[i].enabled && data->elements[i].clickable)
		{
			printf("1\n");
			if (is_in_polygon(x, y, &(data->elements[i].polygon)))
			{
				printf("2\n");
				data->elements[i].on_click_func(data, i);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

uint16_t	find_free_element(t_data *data)
{
	uint32_t	i;
	t_element	*e;

	e = NULL;
	i = 0;
	while (i < data->nb_elements)
	{
		if (!data->elements[i].enabled)
		{
			e = &(data->elements[i]);
			break;
		}
		i++;
	}
	if (!e)
	{
		if (data->nb_elements + 1 >= MAX_ELEMENT_NBR)
		{
			ft_putendl_fd("Error : Couldn't add an element.", 2);
			exit(EXIT_FAILURE);
		}
		e = &(data->elements[i]);
		(data->nb_elements)++;
	}
	e->id = i;
	e->enabled = 1;
	return (e->id);
}


int	mouse_hook(int button, int x,int y, t_data *data)
{
	printf("in mouse_hook.\n");
	printf("paramters : {button : %d, {%d, %d}}\n", button, x, y);
	if (x < 0 || y < 0 || x >= WIN_SIZE_X || y >= WIN_SIZE_Y)
		return (0);
	if (data->input.input_mode == SELECTING)
	{
		if (loop_elems(button, x, y, data))
			return (0);
	}
	else if (data->input.input_mode == DRAWING)
	{
		if (data->input.id_current_element == -1)
			data->input.id_current_element = find_free_element(data);
		draw_edge(data, (t_ivec2){x, y});
		if (data->elements[data->input.id_current_element].polygon.finished)
		{
			data->elements[data->input.id_current_element].clickable = 1;
			data->elements[data->input.id_current_element].on_click_func = print_click;
			data->input.id_current_element = -1;
		}
	}
	return (0);
}
