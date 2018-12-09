#include <editor.h>

void	delete_point(t_ivec2 *point, t_data *data)
{
	printf("delete id %d\n", get_idpoint_from_addr(point, data)); 
	data->used_point[get_idpoint_from_addr(point, data)]--;
}

void	delete_edge(t_edge *edge, const t_data *data)
{
	(void)data;
	(edge->used)--;
}


void	delete_element(t_element *elem, t_data *data)
{
	uint32_t i;

	elem->enabled = 0;
	i = 0;
	while (i < elem->polygon.nb_points)
	{
		delete_edge(elem->polygon.edges[i], data);
		delete_point(elem->polygon.edges[i]->p1, data);
		i++;
	}
	ft_bzero(elem, sizeof(t_element));
}