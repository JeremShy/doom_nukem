#include <editor.h>

void	print_click(t_data *data, uint16_t id)
{
	(void)data;
	printf("clicked element  : %u\n", id);
}

uint8_t check_segment(const t_data *data, const t_ivec2 *new_point, const t_ivec2 *last_point)
{
	uint32_t		j;

	j = 0;
	while (j < data->nb_elements)
	{
		if (data->elements[j].enabled)
		{
			polygon = &data->elements[j].polygon;
			current_edge = 0;
			while (current_edge < polygon->nb_points)
			{
				if (current_edge == polygon->nb_points - 1 && polygon->finished)
				{
					p1 = &polygon->points[current_edge];
					p2 = &polygon->points[0];
				}
				else
				{
					p1 = &polygon->points[current_edge];
					p2 = &polygon->points[current_edge + 1];
				}
				if (is_intersect(*p1, *p2, *last_point, *new_point))
				{
					printf("Intersection error between {{%d, %d}, {%d, %d}} and {{%d, %d}, {%d, %d}}\n", 
						p1->x, p1->y,
						p2->x, p2->y,
						last_point->x, last_point->y,
						new_point->x, new_point->y);
					return (0);
				}
				current_edge++;
			}
		}
		j++;
	}
	return (1);
}
