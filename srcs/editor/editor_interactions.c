#include <editor.h>

void		wall_texture(uint8_t side, t_data *data)
{
	uint16_t *id;

	if (data->input.id_current_element == -1)
		id = &data->input.texture_wall;
	else
		id = &data->elements[data->input.id_current_element].texture_wall;
	printf("id : %hu\n", *id);
	if (side == ARROW_RIGHT)
	{
		if (*id == LAST_TEXTURE)
			*id = FIRST_TEXTURE;
		else
			*id += 1;
	}
	else
	{
		if (*id == FIRST_TEXTURE)
			*id = LAST_TEXTURE;
		else
			*id -= 1;
	}
}

void		up_texture(uint8_t side, t_data *data)
{
	uint16_t *id;

	if (data->input.id_current_element == -1)
		id = &data->input.texture_up;
	else
		id = &data->elements[data->input.id_current_element].texture_up;
	printf("id : %hu\n", *id);
	if (side == ARROW_RIGHT)
	{
		if (*id == LAST_TEXTURE)
			*id = FIRST_TEXTURE;
		else
			*id += 1;
	}
	else
	{
		if (*id == FIRST_TEXTURE)
			*id = LAST_TEXTURE;
		else
			*id -= 1;
	}
}

void		down_texture(uint8_t side, t_data *data)
{
	uint16_t *id;

	if (data->input.id_current_element == -1)
		id = &data->input.texture_down;
	else
		id = &data->elements[data->input.id_current_element].texture_down;
	printf("id : %hu\n", *id);
	if (side == ARROW_RIGHT)
	{
		if (*id == LAST_TEXTURE)
			*id = FIRST_TEXTURE;
		else
			*id += 1;
	}
	else
	{
		if (*id == FIRST_TEXTURE)
			*id = LAST_TEXTURE;
		else
			*id -= 1;
	}
}

void		floor_texture(uint8_t side, t_data *data)
{
	uint16_t *id;

	if (data->input.id_current_element == -1)
		id = &data->input.texture_floor;
	else
		id = &data->elements[data->input.id_current_element].texture_floor;
	printf("id : %hu\n", *id);
	if (side == ARROW_RIGHT)
	{
		if (*id == LAST_TEXTURE)
			*id = FIRST_TEXTURE;
		else
			*id += 1;
	}
	else
	{
		if (*id == FIRST_TEXTURE)
			*id = LAST_TEXTURE;
		else
			*id -= 1;
	}
}

void		ceiling_texture(uint8_t side, t_data *data)
{
	uint16_t *id;

	if (data->input.id_current_element == -1)
		id = &data->input.texture_ceiling;
	else
		id = &data->elements[data->input.id_current_element].texture_ceiling;
	printf("id : %hu\n", *id);
	if (side == ARROW_RIGHT)
	{
		if (*id == LAST_TEXTURE)
			*id = FIRST_TEXTURE;
		else
			*id += 1;
	}
	else
	{
		if (*id == FIRST_TEXTURE)
			*id = LAST_TEXTURE;
		else
			*id -= 1;
	}
}

void		ceil_angle_y(uint8_t side, t_data *data)
{
	int32_t *angle_ceiling_y;

	if (data->input.id_current_element == -1)
		angle_ceiling_y = &data->input.angle_ceiling.y;
	else
		angle_ceiling_y = &data->elements[data->input.id_current_element].angle_ceiling.y;
	if (side == ARROW_LEFT)
		*angle_ceiling_y -= 5;
	else
		*angle_ceiling_y += 5;
	clamp(angle_ceiling_y, -25, 25);
}

void		ceil_angle_x(uint8_t side, t_data *data)
{
	int32_t *angle_ceiling_x;

	if (data->input.id_current_element == -1)
		angle_ceiling_x = &data->input.angle_ceiling.x;
	else
		angle_ceiling_x = &data->elements[data->input.id_current_element].angle_ceiling.x;
	if (side == ARROW_LEFT)
		*angle_ceiling_x -= 5;
	else
		*angle_ceiling_x += 5;
	clamp(angle_ceiling_x, -25, 25);
}

void		ceil_height(uint8_t side, t_data *data)
{
	int16_t *height_ceiling;

	if (data->input.id_current_element == -1)
		height_ceiling = &data->input.height_ceiling;
	else
		height_ceiling = &(data->elements[data->input.id_current_element].height_ceiling);
	if (side == ARROW_LEFT)
		*height_ceiling -= 10;
	else
		*height_ceiling += 10;
	sclamp(height_ceiling, 0, 300);
}

void		floor_angle_y(uint8_t side, t_data *data)
{
	int32_t *angle_floor_y;

	if (data->input.id_current_element == -1)
		angle_floor_y = &data->input.angle_floor.y;
	else
		angle_floor_y = &data->elements[data->input.id_current_element].angle_floor.y;
	if (side == ARROW_LEFT)
		*angle_floor_y -= 5;
	else
		*angle_floor_y += 5;
	clamp(angle_floor_y, -25, 25);
}

void		floor_angle_x(uint8_t side, t_data *data)
{
	int32_t *angle_floor_x;

	if (data->input.id_current_element == -1)
		angle_floor_x = &data->input.angle_floor.x;
	else
		angle_floor_x = &data->elements[data->input.id_current_element].angle_floor.x;
	if (side == ARROW_LEFT)
		*angle_floor_x -= 5;
	else
		*angle_floor_x += 5;
	clamp(angle_floor_x, -25, 25);
}

void		floor_height(uint8_t side, t_data *data)
{
	int16_t *height_floor;

	if (data->input.id_current_element == -1)
		height_floor = &data->input.height_floor;
	else
		height_floor = &data->elements[data->input.id_current_element].height_floor;
	if (side == ARROW_LEFT)
		*height_floor -= 10;
	else
		*height_floor += 10;
	sclamp(height_floor, 0, 300);
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
	*light = *light > 100 ? 100 : *light;
}
