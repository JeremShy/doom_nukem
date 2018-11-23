#include <editor.h>

void		ceil_angle_y(uint8_t side, t_data *data)
{
	if (side == ARROW_LEFT)
	{
		data->input.ceiling_angle_y -= 5;
		data->input.ceiling_angle_y = (int8_t)clamp_value(data->input.ceiling_angle_y, 0, 45);
	}
	else
	{
		data->input.ceiling_angle_y += 5;
		data->input.ceiling_angle_y = (int8_t)clamp_value(data->input.ceiling_angle_y, 0, 45);
	}
}

void		ceil_angle_x(uint8_t side, t_data *data)
{
	if (side == ARROW_LEFT)
	{
		data->input.ceiling_angle_x -= 5;
		data->input.ceiling_angle_x = (int8_t)clamp_value(data->input.ceiling_angle_x, 0, 45);
	}
	else
	{
		data->input.ceiling_angle_x += 5;
		data->input.ceiling_angle_x = (int8_t)clamp_value(data->input.ceiling_angle_x, 0, 45);
	}
}

void		ceil_height(uint8_t side, t_data *data)
{
	if (side == ARROW_LEFT)
	{
		data->input.ceiling_height -= 10;
		data->input.ceiling_height = (int8_t)clamp_value(data->input.ceiling_height, 0, 100);
	}
	else
	{
		data->input.ceiling_height += 10;
		data->input.ceiling_height = (int8_t)clamp_value(data->input.ceiling_height, 0, 100);
	}
}

void		floor_angle_y(uint8_t side, t_data *data)
{
	if (side == ARROW_LEFT)
	{
		data->input.floor_angle_y -= 5;
		data->input.floor_angle_y = (int8_t)clamp_value(data->input.floor_angle_y, 0, 45);
	}
	else
	{
		data->input.floor_angle_y += 5;
		data->input.floor_angle_y = (int8_t)clamp_value(data->input.floor_angle_y, 0, 45);
	}
}

void		floor_angle_x(uint8_t side, t_data *data)
{
	if (side == ARROW_LEFT)
	{
		data->input.floor_angle_x -= 5;
		data->input.floor_angle_x = (int8_t)clamp_value(data->input.floor_angle_x, 0, 45);
	}
	else
	{
		data->input.floor_angle_x += 5;
		data->input.floor_angle_x = (int8_t)clamp_value(data->input.floor_angle_x, 0, 45);
	}
}

void		floor_height(uint8_t side, t_data *data)
{
	if (side == ARROW_LEFT)
	{
		data->input.floor_height -= 10;
		data->input.floor_height = (int8_t)clamp_value(data->input.floor_height, 0, 100);
	}
	else
	{
		data->input.floor_height += 10;
		data->input.floor_height = (int8_t)clamp_value(data->input.floor_height, 0, 100);
	}
}

void		light(uint8_t side, t_data *data)
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