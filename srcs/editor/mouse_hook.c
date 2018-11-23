#include <editor.h>

/*
** Returns 1 if an element is touched, 0 else.
*/

static int8_t	loop_elems(int button, int x,int y, t_data *data)
{
	uint32_t		i;
	float			dist;
	int				id;
	float			tmp_dist;

	i = 0;
	dist = -1;
	if (button != 1)
		return (0);
	while (i < data->nb_elements)
	{
		if (data->elements[i].enabled && data->elements[i].clickable && data->elements[i].polygon.finished)
		{
			tmp_dist = is_in_polygon(x, y, &(data->elements[i].polygon));
			if (tmp_dist != -1 && (tmp_dist < dist || dist == -1))
			{
				dist = tmp_dist;
				id = i;
			}
		}
		i++;
	}
	if (dist != -1)
		data->elements[id].on_click_func(data, id);
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

int		drawing_zone(int button, int x, int y, t_data *data)
{
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

void		ceil_angle_y(uint8_t side, t_data *data)
{
	char	*string;

	if (side == ARROW_LEFT)
		string = "0";
	else if (side == ARROW_RIGHT)
		string = "45";
	else
		string = "not defined";
	mlx_string_put(data->mlx.mlx_ptr, data->mlx.win_ptr, CEIL_ORI_Y_VALUE_SX, CEIL_ORI_Y_VALUE_SY, 0x1D1D1D, string);
}

int		options_zone(int button, int x, int y, t_data *data)
{
	(void)button;
	(void)data;
	if (x > DRAW_SX && y > DRAW_SY && x < DRAW_EX && y < DRAW_EY)
		data->input.input_mode == DRAWING ? switch_select(data) : switch_drawing(data);
	else if (x > WALL_SX && y > WALL_SY && x < WALL_EX && y < WALL_EY)
		data->input.wall_type = SOLID;
	else if (x > PORTAL_SX && y > PORTAL_SY && x < PORTAL_EX && y < PORTAL_EY)
		data->input.wall_type = PORTAL;
	else if (x > WALL_TEXT_LEFT_SX && y > WALL_TEXT_LEFT_SY && x < WALL_TEXT_LEFT_EX && y < WALL_TEXT_LEFT_EY)
		printf("WALL_TEXT_LEFT\n");
	else if (x > WALL_TEXT_RIGHT_SX && y > WALL_TEXT_RIGHT_SY && x < WALL_TEXT_RIGHT_EX && y < WALL_TEXT_RIGHT_EY)
		printf("WALL_TEXT_RIGHT\n");
	
	else if (x > CEIL_ORI_Y_LEFT_SX && y > CEIL_ORI_Y_LEFT_SY && x < CEIL_ORI_Y_LEFT_EX && y < CEIL_ORI_Y_LEFT_EY)
		ceil_angle_y(ARROW_LEFT, data);
	else if (x > CEIL_ORI_Y_RIGHT_SX && y > CEIL_ORI_Y_RIGHT_SY && x < CEIL_ORI_Y_RIGHT_EX && y < CEIL_ORI_Y_RIGHT_EY)
		ceil_angle_y(ARROW_RIGHT, data);
	else if (x > CEIL_ORI_X_LEFT_SX && y > CEIL_ORI_X_LEFT_SY && x < CEIL_ORI_X_LEFT_EX && y < CEIL_ORI_X_LEFT_EY)
		printf("CEIL_ORI_X_LEFT\n");
	else if (x > CEIL_ORI_X_RIGHT_SX && y > CEIL_ORI_X_RIGHT_SY && x < CEIL_ORI_X_RIGHT_EX && y < CEIL_ORI_X_RIGHT_EY)
		printf("CEIL_ORI_X_RIGHT\n");
	else if (x > CEIL_HEIGHT_LEFT_SX && y > CEIL_HEIGHT_LEFT_SY && x < CEIL_HEIGHT_LEFT_EX && y < CEIL_HEIGHT_LEFT_EY)
		printf("CEIL_HEIGHT_LEFT\n");
	else if (x > CEIL_HEIGHT_RIGHT_SX && y > CEIL_HEIGHT_RIGHT_SY && x < CEIL_HEIGHT_RIGHT_EX && y < CEIL_HEIGHT_RIGHT_EY)
		printf("CEIL_HEIGHT_RIGHT\n");
	else if (x > CEIL_TEXT_LEFT_SX && y > CEIL_TEXT_LEFT_SY && x < CEIL_TEXT_LEFT_EX && y < CEIL_TEXT_LEFT_EY)
		printf("CEIL_TEXT_LEFT\n");
	else if (x > CEIL_TEXT_RIGHT_SX && y > CEIL_TEXT_RIGHT_SY && x < CEIL_TEXT_RIGHT_EX && y < CEIL_TEXT_RIGHT_EY)
		printf("CEIL_TEXT_RIGHT\n");
	
	else if (x > FLOOR_ORI_Y_LEFT_SX && y > FLOOR_ORI_Y_LEFT_SY && x < FLOOR_ORI_Y_LEFT_EX && y < FLOOR_ORI_Y_LEFT_EY)
		printf("FLOOR_ORI_Y_LEFT\n");
	else if (x > FLOOR_ORI_Y_RIGHT_SX && y > FLOOR_ORI_Y_RIGHT_SY && x < FLOOR_ORI_Y_RIGHT_EX && y < FLOOR_ORI_Y_RIGHT_EY)
		printf("FLOOR_ORI_Y_RIGHT\n");
	else if (x > FLOOR_ORI_X_LEFT_SX && y > FLOOR_ORI_X_LEFT_SY && x < FLOOR_ORI_X_LEFT_EX && y < FLOOR_ORI_X_LEFT_EY)
		printf("FLOOR_ORI_X_LEFT\n");
	else if (x > FLOOR_ORI_X_RIGHT_SX && y > FLOOR_ORI_X_RIGHT_SY && x < FLOOR_ORI_X_RIGHT_EX && y < FLOOR_ORI_X_RIGHT_EY)
		printf("FLOOR_ORI_X_RIGHT\n");
	else if (x > FLOOR_HEIGHT_LEFT_SX && y > FLOOR_HEIGHT_LEFT_SY && x < FLOOR_HEIGHT_LEFT_EX && y < FLOOR_HEIGHT_LEFT_EY)
		printf("FLOOR_HEIGHT_LEFT\n");
	else if (x > FLOOR_HEIGHT_RIGHT_SX && y > FLOOR_HEIGHT_RIGHT_SY && x < FLOOR_HEIGHT_RIGHT_EX && y < FLOOR_HEIGHT_RIGHT_EY)
		printf("FLOOR_HEIGHT_RIGHT\n");
	else if (x > FLOOR_TEXT_LEFT_SX && y > FLOOR_TEXT_LEFT_SY && x < FLOOR_TEXT_LEFT_EX && y < FLOOR_TEXT_LEFT_EY)
		printf("FLOOR_TEXT_LEFT\n");
	else if (x > FLOOR_TEXT_RIGHT_SX && y > FLOOR_TEXT_RIGHT_SY && x < FLOOR_TEXT_RIGHT_EX && y < FLOOR_TEXT_RIGHT_EY)
		printf("FLOOR_TEXT_RIGHT\n");

	else if (x > UP_TEXT_LEFT_SX && y > UP_TEXT_LEFT_SY && x < UP_TEXT_LEFT_EX && y < UP_TEXT_LEFT_EY)
		printf("UP_TEXT_LEFT\n");
	else if (x > UP_TEXT_RIGHT_SX && y > UP_TEXT_RIGHT_SY && x < UP_TEXT_RIGHT_EX && y < UP_TEXT_RIGHT_EY)
		printf("UP_TEXT_RIGHT\n");
	else if (x > DOWN_TEXT_LEFT_SX && y > DOWN_TEXT_LEFT_SY && x < DOWN_TEXT_LEFT_EX && y < DOWN_TEXT_LEFT_EY)
		printf("DOWN_TEXT_LEFT\n");
	else if (x > DOWN_TEXT_RIGHT_SX && y > DOWN_TEXT_RIGHT_SY && x < DOWN_TEXT_RIGHT_EX && y < DOWN_TEXT_RIGHT_EY)
		printf("DOWN_TEXT_RIGHT\n");
	else if (x > LIGHT_TEXT_LEFT_SX && y > LIGHT_TEXT_LEFT_SY && x < LIGHT_TEXT_LEFT_EX && y < LIGHT_TEXT_LEFT_EY)
		printf("LIGHT_TEXT_LEFT\n");
	else if (x > LIGHT_TEXT_RIGHT_SX && y > LIGHT_TEXT_RIGHT_SY && x < LIGHT_TEXT_RIGHT_EX && y < LIGHT_TEXT_RIGHT_EY)
		printf("LIGHT_TEXT_RIGHT\n");

	else if (x > OBJ_COLL_LEFT_SX && y > OBJ_COLL_LEFT_SY && x < OBJ_COLL_LEFT_EX && y < OBJ_COLL_LEFT_EY)
		printf("OBJ_COLL_LEFT\n");
	else if (x > OBJ_COLL_RIGHT_SX && y > OBJ_COLL_RIGHT_SY && x < OBJ_COLL_RIGHT_EX && y < OBJ_COLL_RIGHT_EY)
		printf("OBJ_COLL_RIGHT\n");
	else if (x > OBJ_SCEN_LEFT_SX && y > OBJ_SCEN_LEFT_SY && x < OBJ_SCEN_LEFT_EX && y < OBJ_SCEN_LEFT_EY)
		printf("OBJ_SCEN_LEFT\n");
	else if (x > OBJ_SCEN_RIGHT_SX && y > OBJ_SCEN_RIGHT_SY && x < OBJ_SCEN_RIGHT_EX && y < OBJ_SCEN_RIGHT_EY)
		printf("OBJ_SCEN_RIGHT\n");
	else if (x > OBJ_PNJ_LEFT_SX && y > OBJ_PNJ_LEFT_SY && x < OBJ_PNJ_LEFT_EX && y < OBJ_PNJ_LEFT_EY)
		printf("OBJ_PNJ_LEFT\n");
	else if (x > OBJ_PNJ_RIGHT_SX && y > OBJ_PNJ_RIGHT_SY && x < OBJ_PNJ_RIGHT_EX && y < OBJ_PNJ_RIGHT_EY)
		printf("OBJ_PNJ_RIGHT\n");
	return (0);
}

int	mouse_hook(int button, int x,int y, t_data *data)
{
	printf("in mouse_hook.\n");
	printf("paramters : {button : %d, {%d, %d}}\n", button, x, y);
	if (x < 0 || y < 0 || x >= WIN_SIZE_X || y >= WIN_SIZE_Y)
		return (0);
	if (x < DRAWING_ZONE_WIDTH)
		drawing_zone(button, x, y, data);
	else
		options_zone(button, x, y, data);
	return (0);
}
