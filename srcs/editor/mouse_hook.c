#include <editor.h>

static uint16_t	find_free_element(t_data *data)
{
	uint32_t	i;
	t_element	*e;

	e = NULL;
	i = 0;
	while (i < data->max_element_id)
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
		if (data->max_element_id + 1 >= MAX_ELEMENT_NBR)
		{
			ft_putendl_fd("Error : Couldn't add an element.", 2);
			exit(EXIT_FAILURE);
		}
		e = &(data->elements[i]);
		(data->max_element_id)++;
	}
	e->light = 100;
	e->texture_floor = IMG_START_TEXTURES;
	e->texture_ceiling = IMG_START_TEXTURES;
	e->polygon.nb_points = 0;
	e->polygon.finished = 0;
	e->id = i;
	e->enabled = 1;
	return (e->id);
}

int		drawing_zone(int x, int y, t_data *data)
{
	t_element	*elem;
	t_edge		*edge;
	float		dist;

	if (data->input.mode == DELETE_SECTOR)
	{ 
		elem = get_polygon_from_point(data, &(t_ivec2){x, y});
		if (elem)
			delete_element(elem, data);
		data->update_drawing = 1;
	}
	else if (data->input.mode == SELECTING)
	{
		data->input.id_current_element = -1;

		if ((edge = get_nearest_edge(&(t_ivec2){x, y}, data, &dist)) && dist < 6)
		{
			data->input.current_edge = edge;
			data->input.id_current_element = -1;
		}
		else if ((elem = get_polygon_from_point(data, &(t_ivec2){x, y})))
		{
				data->input.id_current_element = elem->id;
				data->input.current_edge = NULL;
		}
	}
	else if (data->input.mode == DRAWING)
	{
		if (data->input.id_current_element == -1)
			data->input.id_current_element = find_free_element(data);
		create_edge(data, (t_ivec2){x, y});
		if (data->elements[data->input.id_current_element].polygon.finished)
		{
			data->elements[data->input.id_current_element].clickable = 1;
			data->input.id_current_element = -1;
		}
	}
	else if (data->input.mode == MOVE_POINT)
	{
		if (get_nearest_point(data, &(t_ivec2){x, y}, &data->input.id_current_point) >= 10)
			data->input.id_current_point = -1;

	}
	return (0);
}

static int		options_zone(int button, int x, int y, t_data *data)
{
	(void)button;
	(void)data;
	if (x >= SQUARE_SELECT_SX && y >= SQUARE_SELECT_SY && x <= SQUARE_SELECT_EX && y <= SQUARE_SELECT_EY)
		switch_select(data);
	else if (x >= SQUARE_MOVE_SX && y >= SQUARE_MOVE_SY && x <= SQUARE_MOVE_EX && y <= SQUARE_MOVE_EY)
		switch_move_point(data);
	else if (x >= SQUARE_DELETE_SX && y >= SQUARE_DELETE_SY && x <= SQUARE_DELETE_EX && y <= SQUARE_DELETE_EY)
		switch_delete_sector(data);
	else if (x >= SQUARE_SAVE_SX && y >= SQUARE_SAVE_SY && x <= SQUARE_SAVE_EX && y <= SQUARE_SAVE_EY)
		save_scene(data);
	else if (x >= SQUARE_DRAW_SX && y >= SQUARE_DRAW_SY && x <= SQUARE_DRAW_EX && y <= SQUARE_DRAW_EY)
		switch_drawing(data);
	else if (x > WALL_TYPE_RED_SX && y > WALL_TYPE_RED_SY && x < WALL_TYPE_RED_EX && y < WALL_TYPE_RED_EY)
		data->input.wall_type = PORTAL;
	else if (x > WALL_TYPE_WHITE_SX && y > WALL_TYPE_WHITE_SY && x < WALL_TYPE_WHITE_EX && y < WALL_TYPE_WHITE_EY)
		data->input.wall_type = SOLID;

	if (data->input.mode == SELECTING && data->input.current_edge)
	{
		if (data->input.current_edge->type == PORTAL)
		{
			if (x > UP_LEFT_ARROW_SX && y > UP_LEFT_ARROW_SY && x < UP_LEFT_ARROW_EX && y < UP_LEFT_ARROW_EY)
				up_texture(ARROW_LEFT, data);
			else if (x > UP_RIGHT_ARROW_SX && y > UP_RIGHT_ARROW_SY && x < UP_RIGHT_ARROW_EX && y < UP_RIGHT_ARROW_EY)
				up_texture(ARROW_RIGHT, data);
			else if (x > DOWN_LEFT_ARROW_SX && y > DOWN_LEFT_ARROW_SY && x < DOWN_LEFT_ARROW_EX && y < DOWN_LEFT_ARROW_EY)
				down_texture(ARROW_LEFT, data);
			else if (x > DOWN_RIGHT_ARROW_SX && y > DOWN_RIGHT_ARROW_SY && x < DOWN_RIGHT_ARROW_EX && y < DOWN_RIGHT_ARROW_EY)
				down_texture(ARROW_RIGHT, data);
		}
		else
		{
		if (x > WALL_LEFT_ARROW_SX && y > WALL_LEFT_ARROW_SY && x < WALL_LEFT_ARROW_EX && y < WALL_LEFT_ARROW_EY)
			wall_texture(ARROW_LEFT, data);
		else if (x > WALL_RIGHT_ARROW_SX && y > WALL_RIGHT_ARROW_SY && x < WALL_RIGHT_ARROW_EX && y < WALL_RIGHT_ARROW_EY)
			wall_texture(ARROW_RIGHT, data);
		}
	}
	else if (data->input.mode == SELECTING && data->input.id_current_element != -1)
	{
		if (x > LIGHT_LEFT_ARROW_SX && y > LIGHT_LEFT_ARROW_SY && x < LIGHT_LEFT_ARROW_EX && y < LIGHT_LEFT_ARROW_EY)
			light(ARROW_LEFT, data);
		else if (x > LIGHT_RIGHT_ARROW_SX && y > LIGHT_RIGHT_ARROW_SY && x < LIGHT_RIGHT_ARROW_EX && y < LIGHT_RIGHT_ARROW_EY)
			light(ARROW_RIGHT, data);

		else if (x > CEIL_HEIGHT_LEFT_ARROW_SX && y > CEIL_HEIGHT_LEFT_ARROW_SY && x < CEIL_HEIGHT_LEFT_ARROW_EX && y < CEIL_HEIGHT_LEFT_ARROW_EY)
			ceil_height(ARROW_LEFT, data);
		else if (x > CEIL_HEIGHT_RIGHT_ARROW_SX && y > CEIL_HEIGHT_RIGHT_ARROW_SY && x < CEIL_HEIGHT_RIGHT_ARROW_EX && y < CEIL_HEIGHT_RIGHT_ARROW_EY)
			ceil_height(ARROW_RIGHT, data);
		else if (x > SMALL_X_CEIL_LEFT_ARROW_SX && y > SMALL_X_CEIL_LEFT_ARROW_SY && x < SMALL_X_CEIL_LEFT_ARROW_EX && y < SMALL_X_CEIL_LEFT_ARROW_EY)
			ceil_angle_x(ARROW_LEFT, data);
		else if (x > SMALL_X_CEIL_RIGHT_ARROW_SX && y > SMALL_X_CEIL_RIGHT_ARROW_SY && x < SMALL_X_CEIL_RIGHT_ARROW_EX && y < SMALL_X_CEIL_RIGHT_ARROW_EY)
			ceil_angle_x(ARROW_RIGHT, data);
		else if (x > SMALL_Y_CEIL_LEFT_ARROW_SX && y > SMALL_Y_CEIL_LEFT_ARROW_SY && x < SMALL_Y_CEIL_LEFT_ARROW_EX && y < SMALL_Y_CEIL_LEFT_ARROW_EY)
			ceil_angle_y(ARROW_LEFT, data);
		else if (x > SMALL_Y_CEIL_RIGHT_ARROW_SX && y > SMALL_Y_CEIL_RIGHT_ARROW_SY && x < SMALL_Y_CEIL_RIGHT_ARROW_EX && y < SMALL_Y_CEIL_RIGHT_ARROW_EY)
			ceil_angle_y(ARROW_RIGHT, data);
		else if (x > CEIL_TEXT_LEFT_ARROW_SX && y > CEIL_TEXT_LEFT_ARROW_SY && x < CEIL_TEXT_LEFT_ARROW_EX && y < CEIL_TEXT_LEFT_ARROW_EY)
			ceiling_texture(ARROW_LEFT, data);
		else if (x > CEIL_TEXT_RIGHT_ARROW_SX && y > CEIL_TEXT_RIGHT_ARROW_SY && x < CEIL_TEXT_RIGHT_ARROW_EX && y < CEIL_TEXT_RIGHT_ARROW_EY)
			ceiling_texture(ARROW_RIGHT, data);
	
		else if (x > FLOOR_HEIGHT_LEFT_ARROW_SX && y > FLOOR_HEIGHT_LEFT_ARROW_SY && x < FLOOR_HEIGHT_LEFT_ARROW_EX && y < FLOOR_HEIGHT_LEFT_ARROW_EY)
			floor_height(ARROW_LEFT, data);
		else if (x > FLOOR_HEIGHT_RIGHT_ARROW_SX && y > FLOOR_HEIGHT_RIGHT_ARROW_SY && x < FLOOR_HEIGHT_RIGHT_ARROW_EX && y < FLOOR_HEIGHT_RIGHT_ARROW_EY)
			floor_height(ARROW_RIGHT, data);
		else if (x > SMALL_X_FLOOR_LEFT_ARROW_SX && y > SMALL_X_FLOOR_LEFT_ARROW_SY && x < SMALL_X_FLOOR_LEFT_ARROW_EX && y < SMALL_X_FLOOR_LEFT_ARROW_EY)
			floor_angle_x(ARROW_LEFT, data);
		else if (x > SMALL_X_FLOOR_RIGHT_ARROW_SX && y > SMALL_X_FLOOR_RIGHT_ARROW_SY && x < SMALL_X_FLOOR_RIGHT_ARROW_EX && y < SMALL_X_FLOOR_RIGHT_ARROW_EY)
			floor_angle_x(ARROW_RIGHT, data);
		else if (x > SMALL_Y_FLOOR_LEFT_ARROW_SX && y > SMALL_Y_FLOOR_LEFT_ARROW_SY && x < SMALL_Y_FLOOR_LEFT_ARROW_EX && y < SMALL_Y_FLOOR_LEFT_ARROW_EY)
			floor_angle_y(ARROW_LEFT, data);
		else if (x > SMALL_Y_FLOOR_RIGHT_ARROW_SX && y > SMALL_Y_FLOOR_RIGHT_ARROW_SY && x < SMALL_Y_FLOOR_RIGHT_ARROW_EX && y < SMALL_Y_FLOOR_RIGHT_ARROW_EY)
			floor_angle_y(ARROW_RIGHT, data);
		else if (x > FLOOR_TEXT_LEFT_ARROW_SX && y > FLOOR_TEXT_LEFT_ARROW_SY && x < FLOOR_TEXT_LEFT_ARROW_EX && y < FLOOR_TEXT_LEFT_ARROW_EY)
			floor_texture(ARROW_LEFT, data);
		else if (x > FLOOR_TEXT_RIGHT_ARROW_SX && y > FLOOR_TEXT_RIGHT_ARROW_SY && x < FLOOR_TEXT_RIGHT_ARROW_EX && y < FLOOR_TEXT_RIGHT_ARROW_EY)
			floor_texture(ARROW_RIGHT, data);
	}

	return (0);
}

static uint8_t	check_moving_point(t_data *data, t_ivec2 point, t_ivec2 *current)
{
	int32_t i;
	int32_t j;

	i = 0;
	while (i < data->max_edge_id)
	{
		if (data->edges[i].used)
			if (data->edges[i].p1 == current || data->edges[i].p2 == current)
			{
				j = 0;
				while (j < data->max_edge_id)
				{
					if (data->edges[j].used)
						if (data->edges[j].p1 != current && data->edges[j].p2 != current)
							if (intersect_two_segments(
								data->edges[i].p1 == current ? point : *data->edges[i].p1,
								data->edges[i].p1 == current ? *data->edges[i].p2 : point,
								*data->edges[j].p1, *data->edges[j].p2
							).intersect)
								return (0);
					j++;
				}
			}
		i++;
	}
	return (check_point(data, &point, current));
}

int		mouse_motion(int x, int y, t_data *data)
{
	if (data->input.mode == MOVE_POINT && data->input.button[1] && data->input.id_current_point != -1)
	{
		clamp(&x, 10, DRAWING_ZONE_WIDTH - 10);
		clamp(&y, 10, DRAWING_ZONE_HEIGHT - 10);
		// printf("x = %d, y = %d\n", x, y);
		if (check_moving_point(data, (t_ivec2){x, y}, &data->points[data->input.id_current_point]))
		{
			data->update_drawing = 1;
			data->points[data->input.id_current_point] = (t_ivec2){x, y};
		}
	}
	return (0);
}

int	mouse_press(int button, int x, int y, t_data *data)
{
		printf("On clique en : x = %d, y = %d\n", x, y);
	data->input.button[button] = 1;
	if (x < 0 || y < 0 || x >= WIN_SIZE_X || y >= WIN_SIZE_Y)
		return (0);
	if (y < DRAWING_ZONE_HEIGHT && x < DRAWING_ZONE_WIDTH && button == 1)
	{
		drawing_zone(x, y, data);
	}
	else
		options_zone(button, x, y, data);
	return (0);
}

int	mouse_release(int button, int x,int y, t_data *data)
{
	(void)x;
	(void)y;
	data->input.button[button] = 0;
	data->input.id_current_point = -1;
	return (0);
}
