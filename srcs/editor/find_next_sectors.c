#include <editor.h>
#include <file_format.h>

static uint16_t	get_new_id(t_data *data, uint16_t id)
{
	uint16_t	ret;
	uint16_t	i;

	ret = 0;
	i = 0;
	while (i < id)
	{
		if (data->elements[i].enabled)
			ret++;
		i++;
	}
	return (ret);
}

void	find_next_sectors(t_data *data, struct s_ffwall *wall, struct s_edge *edge)
{
	t_vec2		vector;
	t_vec2		normal;
	t_ivec2		point_1;
	t_ivec2		point_2;
	t_element	*elem;

	vector.x = edge->p2->x - edge->p1->x;
	vector.y = edge->p2->y - edge->p1->y;
	normal.x = vector.y * -1;
	normal.y = vector.x;

	point_1 = find_middle_edge(edge);
	point_2 = find_middle_edge(edge);
	if (fabs(normal.x) > fabs(normal.y))
	{
		point_1.x += (normal.x > 0 ? 1 : -1);
		point_2.x += (normal.x > 0 ? -1 : 1);
	
	}
	else
	{
		point_1.y += (normal.y > 0 ? 1 : -1);;
		point_2.y += (normal.y > 0 ? -1 : 1);
	}
	if ((elem = get_polygon_from_point(data, &point_1)))
		wall->next_sector_1 = get_new_id(data, elem->id);
	else
		wall->next_sector_1 = 0;
	if ((elem = get_polygon_from_point(data, &point_2)))
		wall->next_sector_2 = get_new_id(data, elem->id);
	else
		wall->next_sector_2 = 0;
}
