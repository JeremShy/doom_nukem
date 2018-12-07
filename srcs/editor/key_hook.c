#include <editor.h>

static int		pressed_backquote(t_data *data)
{
	if (data->input.id_current_element == -1 || (data->elements[data->input.id_current_element]).polygon.finished)
		return (0);
	data->update_drawing = 1;
	delete_element(&data->elements[data->input.id_current_element], data);
	data->input.id_current_element = -1;
	return (1);
}

void	switch_delete_sector(t_data *data)
{
	if (data->input.mode == DELETE_SECTOR)
		return ;
	pressed_backquote(data);
	data->input.mode = DELETE_SECTOR;
}

void	switch_move_point(t_data *data)
{
	if (data->input.mode == MOVE_POINT)
		return ;
	pressed_backquote(data);
	data->input.mode = MOVE_POINT;
}

void	draw_polygon(t_polygon *polygon, t_data *data)
{
	uint32_t	edge;

	edge = 0;
	while (edge < polygon->nb_points)
	{
		draw_line(polygon->edges[edge]->p1, polygon->edges[edge]->p2, &data->imgs[IMG_DRAWING], get_color_from_typewall(polygon->edges[edge]->type));
		edge++;
	}
}

void	switch_select(t_data *data)
{
	if (data->input.mode == SELECTING)
		return ;
	pressed_backquote(data);
	data->input.mode = SELECTING;
}

void	switch_drawing(t_data *data)
{
	if (data->input.mode == DRAWING)
		return ;
	data->input.mode = DRAWING;
}

int	key_press(int keycode, t_data *data)
{
	printf("keycode : %d\n", keycode);
	data->input.key[keycode] = 1;
	if (keycode == KEY_ESCAPE)
		exit(EXIT_SUCCESS);
	else if (keycode == KEY_BACKQUOTE)
		pressed_backquote(data);
	else if (keycode == KEY_S)
		switch_select(data);
	else if (keycode == KEY_D)
		switch_drawing(data);
	else if (keycode == KEY_P)
	{
		if (data->input.mode == DRAWING)
			data->input.wall_type = PORTAL;
	}
	else if (keycode == KEY_X)
		switch_delete_sector(data);
	else if (keycode == KEY_L)
		liste_points(data);
	else if (keycode == KEY_E)
		liste_edges(data);
	else if (keycode == KEY_M)
		switch_move_point(data);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	data->input.key[keycode] = 0;
	(void)keycode;
	(void)data;
	return (0);
}