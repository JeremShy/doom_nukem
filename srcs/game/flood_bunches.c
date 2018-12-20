#include <game.h>

uint8_t	can_see_edge(t_data *data, t_edge *edge)
{
	float	total_angle;
	float	angle1;
	float	angle2;

	angle1 = data->angle_dir_point[edge->p1 - data->points];
	angle2 = data->angle_dir_point[edge->p2 - data->points];
	if (angle1 > -HALF_FOV && angle1 < HALF_FOV)
		return (1);
	if (angle2 > -HALF_FOV && angle2 < HALF_FOV)
		return (1);
	if ((angle1 * angle2 > 0))
		return (0);
	total_angle = fabs(angle1) + fabs(angle2);
	if (total_angle < M_PI)
		return (1);
	return (0);
}

int32_t	go_to_next_visible_edge(t_data *data, t_sector *sector, int32_t i)
{
	i++;
	while (i < sector->nb_edges)
	{
		if (data->visible_edges[sector->edges[i]->id])
			return (i);
		i++;
	}
	return (-1);
}

int32_t	go_to_start_bunch(t_data *data, t_sector *sector, int32_t i)
{
	int16_t	id_start;

	id_start = i;
	i--;
	while ((i + sector->nb_edges) % sector->nb_edges != id_start)
	{
		if (!data->visible_edges[sector->edges[(i + sector->nb_edges) % sector->nb_edges]->id])
			return ((i + sector->nb_edges + 1) % sector->nb_edges);
		i--;
	}
	return (id_start);
}

int32_t	go_to_end_bunch(t_data *data, t_sector *sector, int32_t i)
{
	int32_t	id_start;

	id_start = i;
	i++;
	while ((i + sector->nb_edges) % sector->nb_edges != id_start)
	{
		if (!data->visible_edges[sector->edges[(i + sector->nb_edges) % sector->nb_edges]->id])
			return ((i + sector->nb_edges - 1) % sector->nb_edges);
		i++;
	}
	return ((id_start + sector->nb_edges - 1) % sector->nb_edges);
}

void	add_bunch(t_data *data, uint16_t id_sector, uint16_t id_begin, uint16_t id_end)
{
	data->bunches[data->nb_bunches].id_sector = id_sector;
	data->bunches[data->nb_bunches].id_begin = id_begin;
	data->bunches[data->nb_bunches].id_end= id_end;

	do_log("Creating bunch : %d\n", data->nb_bunches);
	do_log("data->bunches[%d].id_sector = %d\n", data->nb_bunches, data->bunches[data->nb_bunches].id_sector);
	do_log("data->bunches[%d].id_begin = %d\n", data->nb_bunches, data->bunches[data->nb_bunches].id_begin);
	do_log("data->bunches[%d].id_end= %d\n", data->nb_bunches, data->bunches[data->nb_bunches].id_end);

	(data->nb_bunches)++;
}

void	add_bunches_from_sector(t_data *data, uint16_t sector)
{
	int32_t	current_edge;
	int32_t	end;
	int32_t	first;

	current_edge = 0;
	if (data->sectors[sector].nb_edges <= 0)
		return ;
	if (!data->visible_edges[data->sectors[sector].edges[current_edge]->id])
		current_edge = go_to_next_visible_edge(data, &data->sectors[sector], current_edge);
	else
		current_edge = go_to_start_bunch(data, &data->sectors[sector], current_edge);
	first = current_edge;
	while (current_edge != -1)
	{
		end = go_to_end_bunch(data, &data->sectors[sector], current_edge);
		add_bunch(data, sector, current_edge, end);
		current_edge = go_to_next_visible_edge(data, &data->sectors[sector], end);
		if (current_edge == first)
			return ;
	}
}

void	flood_bunches(t_data *data)
{
	int			i;
	uint32_t	current_sector;

	i = 0;
	while (i < data->nb_edges)
	{
		data->visible_edges[i] = can_see_edge(data, &data->edges[i]);
		i++;
	}
	current_sector = 0;
	data->nb_bunches = 0;
	while (current_sector < data->nb_sectors)
	{
		add_bunches_from_sector(data, current_sector);
		current_sector++;
	}
}
