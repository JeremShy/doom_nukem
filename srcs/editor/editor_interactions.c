#include <editor.h>

void		wall_texture(uint8_t side, t_data *data)
{
	uint16_t *id;

	if (data->input.current_edge == NULL || data->input.current_edge->type != SOLID)
		return ;
	else
		id = &data->input.current_edge->texture_wall;
	if (side == ARROW_RIGHT)
	{
		if (*id == IMG_START_TEXTURES + data->nbr_textures - 1)
			*id = IMG_START_TEXTURES;
		else
			*id += 1;
	}
	else
	{
		if (*id == IMG_START_TEXTURES)
			*id = IMG_START_TEXTURES + data->nbr_textures - 1;
		else
			*id -= 1;
	}
}

void		up_texture(uint8_t side, t_data *data)
{
	uint16_t *id;

	if (data->input.current_edge == NULL || data->input.current_edge->type != PORTAL)
		return ;
	else
		id = &data->input.current_edge->texture_up;
	if (side == ARROW_RIGHT)
	{
		if (*id == IMG_START_TEXTURES + data->nbr_textures - 1)
			*id = IMG_START_TEXTURES;
		else
			*id += 1;
	}
	else
	{
		if (*id == IMG_START_TEXTURES)
			*id = IMG_START_TEXTURES + data->nbr_textures - 1;
		else
			*id -= 1;
	}
}

void		down_texture(uint8_t side, t_data *data)
{
	uint16_t *id;

	if (data->input.current_edge == NULL || data->input.current_edge->type != PORTAL)
		return ;
	else
		id = &data->input.current_edge->texture_down;
	if (side == ARROW_RIGHT)
	{
		if (*id == IMG_START_TEXTURES + data->nbr_textures - 1)
			*id = IMG_START_TEXTURES;
		else
			*id += 1;
	}
	else
	{
		if (*id == IMG_START_TEXTURES)
			*id = IMG_START_TEXTURES + data->nbr_textures - 1;
		else
			*id -= 1;
	}
}

void		floor_texture(uint8_t side, t_data *data)
{
	uint16_t *id;

	if (data->input.id_current_element == -1)
		return ;
	else
		id = &data->elements[data->input.id_current_element].texture_floor;
	if (side == ARROW_RIGHT)
	{
		if (*id == IMG_START_TEXTURES + data->nbr_textures - 1)
			*id = IMG_START_TEXTURES;
		else
			*id += 1;
	}
	else
	{
		if (*id == IMG_START_TEXTURES)
			*id = IMG_START_TEXTURES + data->nbr_textures - 1;
		else
			*id -= 1;
	}
}

void		ceiling_texture(uint8_t side, t_data *data)
{
	uint16_t *id;

	if (data->input.id_current_element == -1)
		return ;
	else
		id = &data->elements[data->input.id_current_element].texture_ceiling;
	if (side == ARROW_RIGHT)
	{
		if (*id == IMG_START_TEXTURES + data->nbr_textures - 1)
			*id = IMG_START_TEXTURES;
		else
			*id += 1;
	}
	else
	{
		if (*id == IMG_START_TEXTURES)
			*id = IMG_START_TEXTURES + data->nbr_textures - 1;
		else
			*id -= 1;
	}
}

void		ceil_angle_y(uint8_t side, t_data *data)
{
	int32_t *angle_ceiling_y;

	if (data->input.id_current_element == -1)
		return ;
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
		return ;
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
		return ;
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
		return ;
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
		return ;
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
		return ;
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
		return ;
	else
		light = &data->elements[data->input.id_current_element].light;
	if (side == ARROW_LEFT)
		*light -= *light ? 10 : 0;
	else
		*light += 10;
	*light = *light > 100 ? 100 : *light;
}
