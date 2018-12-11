#include <editor.h>

void	delete_point(t_ivec2 *point, t_data *data)
{
	data->used_point[get_idpoint_from_addr(point, data)]--;
	if (data->used_point[get_idpoint_from_addr(point, data)] > 127)
		printf("ERROR on point %d\n", get_idpoint_from_addr(point, data));
	if (get_idpoint_from_addr(point, data) == data->max_point_id - 1)
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
	t_ivec2		*curr;

	elem->enabled = 0;
	i = 0;
	while (i < elem->polygon.nb_points)
	{
		if (i == 0)
		{
			if (elem->polygon.finished)
				curr = elem->polygon.edges[i]->p2;
			else
				curr = elem->polygon.edges[i]->p1;
		}
		else if (curr == elem->polygon.edges[i]->p1)
			curr = elem->polygon.edges[i]->p2;
		else
			curr = elem->polygon.edges[i]->p1;
		delete_edge(elem->polygon.edges[i], data);
		delete_point(curr, data);
		i++;
	}
	if (elem->id == data->nb_elements - 1)
	{
		while (data->nb_elements > 0 && !data->elements[data->nb_elements - 1].enabled)
			(data->nb_elements)--;
	}
}
