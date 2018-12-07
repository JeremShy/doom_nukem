#include <editor.h>

void		ceil_angle_y(uint8_t side, t_data *data)
{
	if (data->input.id_current_element == -1)
	{
		if (side == ARROW_LEFT)
		{
			data->input.angle_ceiling.y -= 5;
			data->input.angle_ceiling.y = (int8_t)clamp_value(data->input.angle_ceiling.y, 0, 45);
		}
		else
		{
			data->input.angle_ceiling.y += 5;
			data->input.angle_ceiling.y = (int8_t)clamp_value(data->input.angle_ceiling.y, 0, 45);
		}
	}
	else
	{
		if (side == ARROW_LEFT)
		{
			data->elements[data->input.id_current_element].angle_ceiling.y -= 5;
			data->elements[data->input.id_current_element].angle_ceiling.y = (int8_t)clamp_value(data->elements[data->input.id_current_element].angle_ceiling.y, 0, 45);
		}
		else
		{
			data->elements[data->input.id_current_element].angle_ceiling.y += 5;
			data->elements[data->input.id_current_element].angle_ceiling.y = (int8_t)clamp_value(data->elements[data->input.id_current_element].angle_ceiling.y, 0, 45);
		}
	}
}

void		ceil_angle_x(uint8_t side, t_data *data)
{
	if (data->input.id_current_element == -1)
	{
		if (side == ARROW_LEFT)
		{
			data->input.angle_ceiling.x -= 5;
			data->input.angle_ceiling.x = (int8_t)clamp_value(data->input.angle_ceiling.x, 0, 45);
		}
		else
		{
			data->input.angle_ceiling.x += 5;
			data->input.angle_ceiling.x = (int8_t)clamp_value(data->input.angle_ceiling.x, 0, 45);
		}
	}
	else
	{
		if (side == ARROW_LEFT)
		{
			data->elements[data->input.id_current_element].angle_ceiling.x -= 5;
			data->elements[data->input.id_current_element].angle_ceiling.x = (int8_t)clamp_value(data->elements[data->input.id_current_element].angle_ceiling.x, 0, 45);
		}
		else
		{
			data->elements[data->input.id_current_element].angle_ceiling.x += 5;
			data->elements[data->input.id_current_element].angle_ceiling.x = (int8_t)clamp_value(data->elements[data->input.id_current_element].angle_ceiling.x, 0, 45);
		}
	}
}

void		ceil_height(uint8_t side, t_data *data)
{
	if (data->input.id_current_element == -1)
	{
		if (side == ARROW_LEFT)
		{
			data->input.height_ceiling -= 10;
			data->input.height_ceiling = (int8_t)clamp_value(data->input.height_ceiling, 0, 100);
		}
		else
		{
			data->input.height_ceiling += 10;
			data->input.height_ceiling = (int8_t)clamp_value(data->input.height_ceiling, 0, 100);
		}
	}
	else
	{
		if (side == ARROW_LEFT)
		{
			data->elements[data->input.id_current_element].height_ceiling -= 10;
			data->elements[data->input.id_current_element].height_ceiling = (int8_t)clamp_value(data->elements[data->input.id_current_element].height_ceiling, 0, 100);
		}
		else
		{
			data->elements[data->input.id_current_element].height_ceiling += 10;
			data->elements[data->input.id_current_element].height_ceiling = (int8_t)clamp_value(data->elements[data->input.id_current_element].height_ceiling, 0, 100);
		}
	}
}

void		floor_angle_y(uint8_t side, t_data *data)
{
	if (data->input.id_current_element == -1)
	{
		if (side == ARROW_LEFT)
		{
			data->input.angle_floor.y -= 5;
			data->input.angle_floor.y = (int8_t)clamp_value(data->input.angle_floor.y, 0, 45);
		}
		else
		{
			data->input.angle_floor.y += 5;
			data->input.angle_floor.y = (int8_t)clamp_value(data->input.angle_floor.y, 0, 45);
		}
	}
	else
	{
		if (side == ARROW_LEFT)
		{
			data->elements[data->input.id_current_element].angle_floor.y -= 5;
			data->elements[data->input.id_current_element].angle_floor.y = (int8_t)clamp_value(data->elements[data->input.id_current_element].angle_floor.y, 0, 45);
		}
		else
		{
			data->elements[data->input.id_current_element].angle_floor.y += 5;
			data->elements[data->input.id_current_element].angle_floor.y = (int8_t)clamp_value(data->elements[data->input.id_current_element].angle_floor.y, 0, 45);
		}
	}
}

void		floor_angle_x(uint8_t side, t_data *data)
{
	if (data->input.id_current_element == -1)
	{
		if (side == ARROW_LEFT)
		{
			data->input.angle_floor.x -= 5;
			data->input.angle_floor.x = (int8_t)clamp_value(data->input.angle_floor.x, 0, 45);
		}
		else
		{
			data->input.angle_floor.x += 5;
			data->input.angle_floor.x = (int8_t)clamp_value(data->input.angle_floor.x, 0, 45);
		}
	}
	else
	{
		if (side == ARROW_LEFT)
		{
			data->elements[data->input.id_current_element].angle_floor.x -= 5;
			data->elements[data->input.id_current_element].angle_floor.x = (int8_t)clamp_value(data->elements[data->input.id_current_element].angle_floor.x, 0, 45);
		}
		else
		{
			data->elements[data->input.id_current_element].angle_floor.x += 5;
			data->elements[data->input.id_current_element].angle_floor.x = (int8_t)clamp_value(data->elements[data->input.id_current_element].angle_floor.x, 0, 45);
		}
	}

}

void		floor_height(uint8_t side, t_data *data)
{
	if (data->input.id_current_element == -1)
	{
		if (side == ARROW_LEFT)
		{
			data->input.height_floor -= 10;
			data->input.height_floor = (int8_t)clamp_value(data->input.height_floor, 0, 100);
		}
		else
		{
			data->input.height_floor += 10;
			data->input.height_floor = (int8_t)clamp_value(data->input.height_floor, 0, 100);
		}
	}
	else
	{
		if (side == ARROW_LEFT)
		{
			data->elements[data->input.id_current_element].height_floor -= 10;
			data->elements[data->input.id_current_element].height_floor = (int8_t)clamp_value(data->elements[data->input.id_current_element].height_floor, 0, 100);
		}
		else
		{
			data->elements[data->input.id_current_element].height_floor += 10;
			data->elements[data->input.id_current_element].height_floor = (int8_t)clamp_value(data->elements[data->input.id_current_element].height_floor, 0, 100);
		}
	}
}

void		light(uint8_t side, t_data *data)
{
	if (data->input.id_current_element == -1)
	{
		if (side == ARROW_LEFT)
		{
			data->input.light -= 10;
			data->input.light = (int8_t)clamp_value(data->input.light, 0, 100);
		}
		else
		{
			data->input.light += 10;
			data->input.light = (int8_t)clamp_value(data->input.light, 0, 100);
		}
	}
	else
	{
		if (side == ARROW_LEFT)
		{
			data->elements[data->input.id_current_element].light -= 10;
			data->elements[data->input.id_current_element].light = (int8_t)clamp_value(data->elements[data->input.id_current_element].light, 0, 100);
		}
		else
		{
			data->elements[data->input.id_current_element].light += 10;
			data->elements[data->input.id_current_element].light = (int8_t)clamp_value(data->elements[data->input.id_current_element].light, 0, 100);
		}
	}
}