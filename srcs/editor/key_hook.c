#include <editor.h>

void	draw_polygon(t_polygon *polygon, t_data *data)
{
	uint32_t	edge;
	t_ivec2		*p1;
	t_ivec2		*p2;

	edge = 0;
	while (edge < polygon->nb_points)
	{
		if (edge == polygon->nb_points - 1)
		{
			p1 = polygon->points[edge];
			p2 = polygon->points[0];
		}
		else
		{
			p1 = polygon->points[edge];
			p2 = polygon->points[edge + 1];
		}
		draw_line(p1, p2, &data->imgs[IMG_DRAWING], get_color_from_typewall(polygon->edges[edge]->type));
		edge++;
	}
}

int	pressed_backquote(t_data *data)
{
	uint32_t	i;
	if (data->input.id_current_element == -1)
	{
		return (0);
	}
	else
	{
		// polygon redraw

		fill_img(&data->imgs[IMG_DRAWING], get_color_code(0, 0, 0, 255));
		i = 0;
		while (i < data->nb_elements)
		{
			if ((int32_t)i != data->input.id_current_element && data->elements[i].enabled)
				draw_polygon(&data->elements[i].polygon, data);
			i++;
		}
	}
	ft_bzero(&data->elements[data->input.id_current_element], sizeof(t_element));
	data->input.id_current_element = -1;
	return (1);
}

void	switch_select(t_data *data)
{
	if (data->input.input_mode == SELECTING)
		return ;
	pressed_backquote(data);
	data->input.input_mode = SELECTING;
}

void	switch_drawing(t_data *data)
{
	if (data->input.input_mode == DRAWING)
		return ;
	data->input.input_mode = DRAWING;
}

int	key_hook(int keycode, t_data *data)
{
	(void)data;
	printf("keycode : %d\n", keycode);
	if (keycode == KEY_ESCAPE)
	{
		exit(EXIT_SUCCESS);
	}
	else if (keycode == KEY_BACKQUOTE)
	{
		pressed_backquote(data);
	}
	else if (keycode == KEY_S)
	{
		switch_select(data);
	}
	else if (keycode == KEY_D)
	{
		switch_drawing(data);
	}
	else if (keycode == KEY_P)
	{
		if (data->input.input_mode == DRAWING)
			data->input.wall_type = PORTAL;
	}
	return (0);
}
