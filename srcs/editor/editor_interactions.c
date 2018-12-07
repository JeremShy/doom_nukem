#include <editor.h>

void		ceil_angle_y(uint8_t side, t_data *data)
{
	int32_t *ceil_angle_y;

	if (data->input.id_current_element == -1)
		ceil_angle_y = &data->input.angle_ceiling.y;
	else
		ceil_angle_y = &data->elements[data->input.id_current_element].angle_ceiling.y;
	if (side == ARROW_LEFT)
		*ceil_angle_y -= *ceil_angle_y ? 5 : 0;
	else
		*ceil_angle_y += 5;
	*ceil_angle_y = (int8_t)clamp_value(*ceil_angle_y, 0, 45);
}

void		ceil_angle_x(uint8_t side, t_data *data)
{
	int32_t *ceil_angle_x;

	if (data->input.id_current_element == -1)
		ceil_angle_x = &data->input.angle_ceiling.x;
	else
		ceil_angle_x = &data->elements[data->input.id_current_element].angle_ceiling.x;
	if (side == ARROW_LEFT)
		*ceil_angle_x -= *ceil_angle_x ? 5 : 0;
	else
		*ceil_angle_x += 5;
	*ceil_angle_x = (int8_t)clamp_value(*ceil_angle_x, 0, 45);
}

void		ceil_height(uint8_t side, t_data *data)
{
	uint8_t *ceil_height;

	if (data->input.id_current_element == -1)
		ceil_height = &data->input.height_ceiling;
	else
		ceil_height = &data->elements[data->input.id_current_element].height_ceiling;
	if (side == ARROW_LEFT)
		*ceil_height -= *ceil_height ? 10 : 0;
	else
		*ceil_height += 10;
	*ceil_height = (int8_t)clamp_value(*ceil_height, 0, 100);
}

void		floor_angle_y(uint8_t side, t_data *data)
{
	int32_t *floor_angle_y;

	if (data->input.id_current_element == -1)
		floor_angle_y = &data->input.angle_floor.y;
	else
		floor_angle_y = &data->elements[data->input.id_current_element].angle_floor.y;
	if (side == ARROW_LEFT)
		*floor_angle_y -= *floor_angle_y ? 5 : 0;
	else
		*floor_angle_y += 5;
	*floor_angle_y = (int8_t)clamp_value(*floor_angle_y, 0, 45);
}

void		floor_angle_x(uint8_t side, t_data *data)
{
	int32_t *floor_angle_x;

	if (data->input.id_current_element == -1)
		floor_angle_x = &data->input.angle_floor.x;
	else
		floor_angle_x = &data->elements[data->input.id_current_element].angle_floor.x;
	if (side == ARROW_LEFT)
		*floor_angle_x -= *floor_angle_x ? 5 : 0;
	else
		*floor_angle_x += 5;
	*floor_angle_x = (int8_t)clamp_value(*floor_angle_x, 0, 45);
}

void		floor_height(uint8_t side, t_data *data)
{
	uint8_t *floor_height;

	if (data->input.id_current_element == -1)
		floor_height = &data->input.height_floor;
	else
		floor_height = &data->elements[data->input.id_current_element].height_floor;
	if (side == ARROW_LEFT)
		*floor_height -= *floor_height ? 10 : 0;
	else
		*floor_height += 10;
	*floor_height = (int8_t)clamp_value(*floor_height, 0, 100);
}

void		light(uint8_t side, t_data *data)
{
	uint32_t *light;

	if (data->input.id_current_element == -1)
		light = &data->input.light;
	else
		light = &data->elements[data->input.id_current_element].light;
	if (side == ARROW_LEFT)
		*light -= *light ? 10 : 0;
	else
		*light += 10;
	*light = (int8_t)clamp_value(*light, 0, 100);
}