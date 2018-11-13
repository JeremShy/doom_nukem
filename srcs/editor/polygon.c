#include <editor.h>

void	clicked_polygon(t_data *data, int id)
{
	printf("in polygon_on_click.\n");
}

int8_t	is_in_polygon(int x, int y, t_polygon rect)
{
	return (0);
}

static uint32_t	find_next_available(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_params)
	{
		if (data->params[i].enabled == 0)
			return (i);
		i++;
	}
	(data->nb_params)++;
	return (data->nb_params - 1);
}

void draw_edge(t_data *data, t_ivec2 new_point, t_wall type)
{
	static	t_polygon polygon = {-1, SOLID, 0, 0, {{0, 0}}, NULL};

	if (polygon.enabled == 0)
	{

	}
}
