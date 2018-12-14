#include <editor.h>

void	delete_point(t_ivec2 *point, t_data *data)
{
	data->used_point[get_idpoint_from_addr(point, data)]--;
	printf("DELETE POINT ID = %lu\n", point - data->points);
	if (data->used_point[get_idpoint_from_addr(point, data)] > 127)
		printf("ERROR on point %d\n", get_idpoint_from_addr(point, data));
	if (point - data->points == data->max_point_id - 1)
	{
		while (data->max_point_id > 0 && !data->used_point[data->max_point_id - 1])
			(data->max_point_id)--;
	}
}

void	delete_edge(t_edge *edge, t_data *data)
{
	(edge->used)--;
	if (edge - data->edges == data->max_edge_id - 1)
	{
		while (data->max_edge_id > 0 && !data->edges[data->max_edge_id - 1].used)
			(data->max_edge_id)--;
	}
}

void	delete_element(t_element *elem, t_data *data)
{
	uint32_t	i;
	t_ivec2		*next;


	elem->enabled = 0;
	if (elem->polygon.nb_points > 1)
	{
		if (elem->polygon.edges[0]->p1 == elem->polygon.edges[1]->p1 || elem->polygon.edges[0]->p1 == elem->polygon.edges[1]->p2)
			next = elem->polygon.edges[0]->p2;
		else
			next = elem->polygon.edges[0]->p1;
	}
	else
		next = elem->polygon.edges[0]->p1 == NULL ? elem->polygon.edges[0]->p2 : elem->polygon.edges[0]->p1;
	i = 0;
	while (i < elem->polygon.nb_points)
	{
		if (next == elem->polygon.edges[i]->p1)
		{
			delete_point(elem->polygon.edges[i]->p1, data);
			next = elem->polygon.edges[i]->p2;
		}
		else
		{
			delete_point(elem->polygon.edges[i]->p2, data);
			next = elem->polygon.edges[i]->p1;
		}
		delete_edge(elem->polygon.edges[i], data);
		i++;
	}
	if (elem->id == data->max_element_id - 1)
	{
		while (data->max_element_id > 0 && !data->elements[data->max_element_id - 1].enabled)
			(data->max_element_id)--;
	}
}
