#include <editor.h>

/*
** Returns 1 if an element is touched, 0 else.
*/

int16_t	loop_elems(int button, int x,int y, t_data *data)
{
	uint32_t		i;
	float			dist;
	int				id;
	float			tmp_dist;

	i = 0;
	id = 0;
	dist = -1;
	if (button != 1)
		return (0);
	while (i < data->nb_elements)
	{
		if (data->elements[i].enabled && data->elements[i].clickable && data->elements[i].polygon.finished)
		{
			tmp_dist = is_in_polygon(x, y, &(data->elements[i].polygon));
			// printf("dist with polygon %d : %f\n", i, tmp_dist);
			if (tmp_dist != -1 && ((tmp_dist < dist && data->elements[id].polygon.in_element != data->elements[i].id) || dist == -1 || data->elements[data->elements[i].id].polygon.in_element == data->elements[id].id))
			{
				dist = tmp_dist;
				id = i;
			}
		}
		i++;
	}
	if (dist != -1)
	{
		// data->elements[id].on_click_func(data, id);
		return (id);
	}
	return (-1);
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
	int id;
	printf("in mouse_hook.\n");
	printf("paramters : {button : %d, {%d, %d}}\n", button, x, y);
	if (x < 0 || y < 0 || x >= WIN_SIZE_X || y >= WIN_SIZE_Y)
		return (0);
	if (data->input.input_mode == SELECTING)
	{
		id = loop_elems(button, x, y, data);
		if (id >= 0)
			data->elements[id].on_click_func(data, id);
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
