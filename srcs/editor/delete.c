#include <editor.h>

void	delete_point(t_ivec2 *point, t_data *data)
{
	// printf("delete id %d\n", get_idpoint_from_addr(point, data)); 
	data->used_point[get_idpoint_from_addr(point, data)]--;
	if (data->used_point[get_idpoint_from_addr(point, data)] > 127)
		printf("ERROR on point %d\n", get_idpoint_from_addr(point, data));
}

void	delete_edge(t_edge *edge, const t_data *data)
{
	(void)data;
	(edge->used)--;
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
	// ft_bzero(elem, sizeof(t_element));
}

// void	delete_element(t_element *elem, t_data *data)
// {
// 	uint32_t	i;
// 	t_ivec2		*start_point;
// 	t_ivec2		*last_delete;


// 	elem->enabled = 0;
// 	i = 0;
// 	while (i < elem->polygon.nb_points)
// 	{
// 		if (!start_point)
// 		{
// 			start_point = elem->polygon.edges[i]->p1;
// 			last_delete = elem->polygon.edges[i]->p1;
// 		}
// 		delete_edge(elem->polygon.edges[i], data);
// 		if (elem->polygon.edges[i]->p1 == last_delete)
// 		{
// 			last_delete = elem->polygon.edges[i]->p2;
// 			delete_point(elem->polygon.edges[i]->p2, data);
// 		}
// 		else
// 		{
// 			last_delete = elem->polygon.edges[i]->p1;
// 			delete_point(elem->polygon.edges[i]->p1, data);
// 		}
// 		if (last_delete == start_point)
// 			return ;
// 		i++;
// 	}
// 	// ft_bzero(elem, sizeof(t_element));
// }
