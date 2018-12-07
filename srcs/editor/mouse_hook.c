#include <editor.h>

t_element *get_polygon_from_point(t_data *data, t_ivec2 point)
{
	uint32_t		i;
	float			dist;
	int				id;
	float			tmp_dist;

	i = 0;
	dist = -1;
	while (i < data->nb_elements)
	{
		if (data->elements[i].enabled && data->elements[i].clickable && data->elements[i].polygon.finished)
		{
			tmp_dist = is_in_polygon(point.x, point.y, &(data->elements[i].polygon));
			if (tmp_dist != -1 && (tmp_dist < dist || dist == -1))
			{
				dist = tmp_dist;
				id = i;
			}
		}
		i++;
	}
	if (dist != -1)
		return (&data->elements[id]);
	return (NULL);
}

static uint16_t	find_free_element(t_data *data)
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
	e->light = 100;
	e->texture_floor = 1;
	e->texture_ceiling = 2; 
	e->texture_up = 3;
	e->texture_down = 1;
	e->texture_wall = 2;
	e->id = i;
	e->enabled = 1;
	return (e->id);
}

// static void		update_input(t_data *data)
// {
// 	data->input.ceiling_angle_y;
// 	data->input.ceiling_angle_x;
// 	data->input.ceiling_height;
// 	data->input.floor_angle_y;
// 	data->input.floor_angle_x;
// 	data->input.floor_height;
// 	data->input.light;
// }

static int		drawing_zone(int x, int y, t_data *data)
{
	// t_ivec2		p;
	t_element	*elem;
	// float		dist;

	if (data->input.mode == DELETE_SECTOR)
	{
		elem = get_polygon_from_point(data, (t_ivec2){x, y});
		if (elem)
			delete_element(elem, data);
		data->update_drawing = 1;
	}
	else if (data->input.mode == SELECTING)
	{
		data->input.id_current_element = -1;
		elem = get_polygon_from_point(data, (t_ivec2){x, y});
		if (elem)
			data->input.id_current_element = elem->id;

	}
	else if (data->input.mode == DRAWING)
	{
		if (data->input.id_current_element == -1)
			data->input.id_current_element = find_free_element(data);
		printf("draw\n");
		create_edge(data, (t_ivec2){x, y});
		if (data->elements[data->input.id_current_element].polygon.finished)
		{
			data->elements[data->input.id_current_element].clickable = 1;
			data->elements[data->input.id_current_element].on_click_func = print_click;
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
		exit(EXIT_SUCCESS);
	else if (x >= SQUARE_DRAW_SX && y >= SQUARE_DRAW_SY && x <= SQUARE_DRAW_EX && y <= SQUARE_DRAW_EY)
		switch_drawing(data);
	else if (x > WALL_TYPE_RED_SX && y > WALL_TYPE_RED_SY && x < WALL_TYPE_RED_EX && y < WALL_TYPE_RED_EY)
		switch_wall_type(data);
	else if (x > WALL_TYPE_WHITE_SX && y > WALL_TYPE_WHITE_SY && x < WALL_TYPE_WHITE_EX && y < WALL_TYPE_WHITE_EY)
		switch_wall_type(data);

	if (data->input.mode == SELECTING && data->input.id_current_element != -1)
	{
		if (x > LIGHT_LEFT_ARROW_SX && y > LIGHT_LEFT_ARROW_SY && x < LIGHT_LEFT_ARROW_EX && y < LIGHT_LEFT_ARROW_EY)
			light(ARROW_LEFT, data);
		else if (x > LIGHT_RIGHT_ARROW_SX && y > LIGHT_RIGHT_ARROW_SY && x < LIGHT_RIGHT_ARROW_EX && y < LIGHT_RIGHT_ARROW_EY)
			light(ARROW_RIGHT, data);

		else if (x > WALL_LEFT_ARROW_SX && y > WALL_LEFT_ARROW_SY && x < WALL_LEFT_ARROW_EX && y < WALL_LEFT_ARROW_EY)
			wall_texture(ARROW_LEFT, data);
		else if (x > WALL_RIGHT_ARROW_SX && y > WALL_RIGHT_ARROW_SY && x < WALL_RIGHT_ARROW_EX && y < WALL_RIGHT_ARROW_EY)
			wall_texture(ARROW_RIGHT, data);

		else if (x > UP_LEFT_ARROW_SX && y > UP_LEFT_ARROW_SY && x < UP_LEFT_ARROW_EX && y < UP_LEFT_ARROW_EY)
			up_texture(ARROW_LEFT, data);
		else if (x > UP_RIGHT_ARROW_SX && y > UP_RIGHT_ARROW_SY && x < UP_RIGHT_ARROW_EX && y < UP_RIGHT_ARROW_EY)
			up_texture(ARROW_RIGHT, data);
		else if (x > DOWN_LEFT_ARROW_SX && y > DOWN_LEFT_ARROW_SY && x < DOWN_LEFT_ARROW_EX && y < DOWN_LEFT_ARROW_EY)
			down_texture(ARROW_LEFT, data);
		else if (x > DOWN_RIGHT_ARROW_SX && y > DOWN_RIGHT_ARROW_SY && x < DOWN_RIGHT_ARROW_EX && y < DOWN_RIGHT_ARROW_EY)
			down_texture(ARROW_RIGHT, data);

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


	// if (x > DRAW_SX && y > DRAW_SY && x < DRAW_EX && y < DRAW_EY)
	// 	data->input.mode == DRAWING ? switch_select(data) : switch_drawing(data);
	// else if (x > WALL_SX && y > WALL_SY && x < WALL_EX && y < WALL_EY)
	// 	data->input.wall_type = SOLID;
	// else if (x > PORTAL_SX && y > PORTAL_SY && x < PORTAL_EX && y < PORTAL_EY)
	// 	data->input.wall_type = PORTAL;
	// else if (x > WALL_TEXT_LEFT_SX && y > WALL_TEXT_LEFT_SY && x < WALL_TEXT_LEFT_EX && y < WALL_TEXT_LEFT_EY)
	// 	printf("WALL_TEXT_LEFT\n");
	// else if (x > WALL_TEXT_RIGHT_SX && y > WALL_TEXT_RIGHT_SY && x < WALL_TEXT_RIGHT_EX && y < WALL_TEXT_RIGHT_EY)
	// 	printf("WALL_TEXT_RIGHT\n");
	
	// else if (x > CEIL_ORI_Y_LEFT_SX && y > CEIL_ORI_Y_LEFT_SY && x < CEIL_ORI_Y_LEFT_EX && y < CEIL_ORI_Y_LEFT_EY)
	// 	ceil_angle_y(ARROW_LEFT, data);
	// else if (x > CEIL_ORI_Y_RIGHT_SX && y > CEIL_ORI_Y_RIGHT_SY && x < CEIL_ORI_Y_RIGHT_EX && y < CEIL_ORI_Y_RIGHT_EY)
	// 	ceil_angle_y(ARROW_RIGHT, data);
	// else if (x > CEIL_ORI_X_LEFT_SX && y > CEIL_ORI_X_LEFT_SY && x < CEIL_ORI_X_LEFT_EX && y < CEIL_ORI_X_LEFT_EY)
	// 	ceil_angle_x(ARROW_LEFT, data);
	// else if (x > CEIL_ORI_X_RIGHT_SX && y > CEIL_ORI_X_RIGHT_SY && x < CEIL_ORI_X_RIGHT_EX && y < CEIL_ORI_X_RIGHT_EY)
	// 	ceil_angle_x(ARROW_RIGHT, data);
	// else if (x > CEIL_HEIGHT_LEFT_SX && y > CEIL_HEIGHT_LEFT_SY && x < CEIL_HEIGHT_LEFT_EX && y < CEIL_HEIGHT_LEFT_EY)
	// 	ceil_height(ARROW_LEFT, data);
	// else if (x > CEIL_HEIGHT_RIGHT_SX && y > CEIL_HEIGHT_RIGHT_SY && x < CEIL_HEIGHT_RIGHT_EX && y < CEIL_HEIGHT_RIGHT_EY)
	// 	ceil_height(ARROW_RIGHT, data);
	// else if (x > CEIL_TEXT_LEFT_SX && y > CEIL_TEXT_LEFT_SY && x < CEIL_TEXT_LEFT_EX && y < CEIL_TEXT_LEFT_EY)
	// 	printf("CEIL_TEXT_LEFT\n");
	// else if (x > CEIL_TEXT_RIGHT_SX && y > CEIL_TEXT_RIGHT_SY && x < CEIL_TEXT_RIGHT_EX && y < CEIL_TEXT_RIGHT_EY)
	// 	printf("CEIL_TEXT_RIGHT\n");
	
	// else if (x > FLOOR_ORI_Y_LEFT_SX && y > FLOOR_ORI_Y_LEFT_SY && x < FLOOR_ORI_Y_LEFT_EX && y < FLOOR_ORI_Y_LEFT_EY)
	// 	floor_angle_y(ARROW_LEFT, data);
	// else if (x > FLOOR_ORI_Y_RIGHT_SX && y > FLOOR_ORI_Y_RIGHT_SY && x < FLOOR_ORI_Y_RIGHT_EX && y < FLOOR_ORI_Y_RIGHT_EY)
	// 	floor_angle_y(ARROW_RIGHT, data);
	// else if (x > FLOOR_ORI_X_LEFT_SX && y > FLOOR_ORI_X_LEFT_SY && x < FLOOR_ORI_X_LEFT_EX && y < FLOOR_ORI_X_LEFT_EY)
	// 	floor_angle_x(ARROW_LEFT, data);
	// else if (x > FLOOR_ORI_X_RIGHT_SX && y > FLOOR_ORI_X_RIGHT_SY && x < FLOOR_ORI_X_RIGHT_EX && y < FLOOR_ORI_X_RIGHT_EY)
	// 	floor_angle_x(ARROW_RIGHT, data);
	// else if (x > FLOOR_HEIGHT_LEFT_SX && y > FLOOR_HEIGHT_LEFT_SY && x < FLOOR_HEIGHT_LEFT_EX && y < FLOOR_HEIGHT_LEFT_EY)
	// 	floor_height(ARROW_LEFT, data);
	// else if (x > FLOOR_HEIGHT_RIGHT_SX && y > FLOOR_HEIGHT_RIGHT_SY && x < FLOOR_HEIGHT_RIGHT_EX && y < FLOOR_HEIGHT_RIGHT_EY)
	// 	floor_height(ARROW_RIGHT, data);
	// else if (x > FLOOR_TEXT_LEFT_SX && y > FLOOR_TEXT_LEFT_SY && x < FLOOR_TEXT_LEFT_EX && y < FLOOR_TEXT_LEFT_EY)
	// 	printf("FLOOR_TEXT_LEFT\n");
	// else if (x > FLOOR_TEXT_RIGHT_SX && y > FLOOR_TEXT_RIGHT_SY && x < FLOOR_TEXT_RIGHT_EX && y < FLOOR_TEXT_RIGHT_EY)
	// 	printf("FLOOR_TEXT_RIGHT\n");

	// else if (x > UP_TEXT_LEFT_SX && y > UP_TEXT_LEFT_SY && x < UP_TEXT_LEFT_EX && y < UP_TEXT_LEFT_EY)
	// 	printf("UP_TEXT_LEFT\n");
	// else if (x > UP_TEXT_RIGHT_SX && y > UP_TEXT_RIGHT_SY && x < UP_TEXT_RIGHT_EX && y < UP_TEXT_RIGHT_EY)
	// 	printf("UP_TEXT_RIGHT\n");
	// else if (x > DOWN_TEXT_LEFT_SX && y > DOWN_TEXT_LEFT_SY && x < DOWN_TEXT_LEFT_EX && y < DOWN_TEXT_LEFT_EY)
	// 	printf("DOWN_TEXT_LEFT\n");
	// else if (x > DOWN_TEXT_RIGHT_SX && y > DOWN_TEXT_RIGHT_SY && x < DOWN_TEXT_RIGHT_EX && y < DOWN_TEXT_RIGHT_EY)
	// 	printf("DOWN_TEXT_RIGHT\n");
	// else if (x > LIGHT_TEXT_LEFT_SX && y > LIGHT_TEXT_LEFT_SY && x < LIGHT_TEXT_LEFT_EX && y < LIGHT_TEXT_LEFT_EY)
	// 	light(ARROW_LEFT, data);
	// else if (x > LIGHT_TEXT_RIGHT_SX && y > LIGHT_TEXT_RIGHT_SY && x < LIGHT_TEXT_RIGHT_EX && y < LIGHT_TEXT_RIGHT_EY)
	// 	light(ARROW_RIGHT, data);

	// else if (x > OBJ_COLL_LEFT_SX && y > OBJ_COLL_LEFT_SY && x < OBJ_COLL_LEFT_EX && y < OBJ_COLL_LEFT_EY)
	// 	printf("OBJ_COLL_LEFT\n");
	// else if (x > OBJ_COLL_RIGHT_SX && y > OBJ_COLL_RIGHT_SY && x < OBJ_COLL_RIGHT_EX && y < OBJ_COLL_RIGHT_EY)
	// 	printf("OBJ_COLL_RIGHT\n");
	// else if (x > OBJ_SCEN_LEFT_SX && y > OBJ_SCEN_LEFT_SY && x < OBJ_SCEN_LEFT_EX && y < OBJ_SCEN_LEFT_EY)
	// 	printf("OBJ_SCEN_LEFT\n");
	// else if (x > OBJ_SCEN_RIGHT_SX && y > OBJ_SCEN_RIGHT_SY && x < OBJ_SCEN_RIGHT_EX && y < OBJ_SCEN_RIGHT_EY)
	// 	printf("OBJ_SCEN_RIGHT\n");
	// else if (x > OBJ_PNJ_LEFT_SX && y > OBJ_PNJ_LEFT_SY && x < OBJ_PNJ_LEFT_EX && y < OBJ_PNJ_LEFT_EY)
	// 	printf("OBJ_PNJ_LEFT\n");
	// else if (x > OBJ_PNJ_RIGHT_SX && y > OBJ_PNJ_RIGHT_SY && x < OBJ_PNJ_RIGHT_EX && y < OBJ_PNJ_RIGHT_EY)
	// 	printf("OBJ_PNJ_RIGHT\n");
	return (0);
}

static uint8_t	check_moving_point(t_data *data, t_ivec2 point, t_ivec2 *current)
{
	uint32_t i;
	uint32_t j;

	i = 0;
	while (i < MAX_POINTS_NBR)
	{
		if (data->edges[i].used)
			if (data->edges[i].p1 == current || data->edges[i].p2 == current)
			{
				j = 0;
				while (j < MAX_POINTS_NBR)
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
		printf("x = %d, y = %d\n", x, y);
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
		printf("I press drawing\n");
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
