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
void	delete_edge(t_edge *edge, const t_data *data)
{
	uint32_t i;
	uint32_t y;

	y = 0;
	while (y < data->nb_elements)
	{
		if (data->elements[y].enabled)
		{
			i = 0;
			while (i < data->elements[y].polygon.nb_points)
			{
				if (data->elements[y].polygon.edges[i] && data->elements[y].polygon.edges[i]->used && edge == data->elements[y].polygon.edges[i])
					return ;
				i++;
			}
		}
		y++;
	}
	ft_bzero(edge, sizeof(t_edge));
}

uint32_t	get_idpoint_from_addr(t_ivec2 *point, t_data *data)
{
	return ((point - data->points) / sizeof(t_ivec2));
}

void	delete_element(t_element *elem, t_data *data)
{
	uint32_t i;

	elem->enabled = 0;
	i = 0;
	while (i < elem->polygon.nb_points - 1)
	{
		delete_edge(elem->polygon.edges[i], data);
		data->used_point[i]--;
		i++;
	}
	if (elem->polygon.finished)
		delete_edge(elem->polygon.edges[i], data);
	data->used_point[i]--;
	ft_bzero(elem, sizeof(t_element));
}

int		pressed_backquote(t_data *data)
{
	if (data->input.id_current_element == -1)
		return (0);
	else
		data->update_drawing = 1;
	delete_element(&data->elements[data->input.id_current_element], data);
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

void	switch_delete_sector(t_data *data)
{
	if (data->input.input_mode == DELETE_SECTOR)
		return ;
	pressed_backquote(data);
	data->input.input_mode = DELETE_SECTOR;
}

void	liste_points(t_data *data)
{
	int i;

	i = 0;
	printf("POINT : -------------\n");
	while (i < MAX_POINTS_NBR)
	{
		if (data->used_point[i])
			printf("point[%u] = {%u, %u}\n", i, data->points[i].x, data->points[i].y);
		i++;
	}
}

int	key_hook(int keycode, t_data *data)
{
	(void)data;
	printf("keycode : %d\n", keycode);
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
		if (data->input.input_mode == DRAWING)
			data->input.wall_type = PORTAL;
	}
	else if (keycode == KEY_X)
		switch_delete_sector(data);
	else if (keycode == KEY_L)
		liste_points(data);
	return (0);
}
