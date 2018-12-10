#include <editor.h>

size_t	calculate_nb_edges(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < MAX_POINTS_NBR)
	{
		if (data->edges[i].used)
			ret++;
		i++;
	}
	return (ret);
}

size_t	calculate_nb_sectors(t_data *data)
{
	uint32_t	i;
	int			ret;

	i = 0;
	ret = 0;
	while (i < data->nb_elements)
	{
		if (data->elements[i].enabled)
			ret++;
		i++;
	}
	return (ret);
}
