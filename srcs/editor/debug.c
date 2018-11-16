#include <editor.h>

void	print_points_list(const t_data *data)
{
	int	i;

	i = 0;
	while (i < MAX_POINTS_NBR)
	{
		if (data->used_point[i] == 1)
		{
			printf("points[%d] : {%d, %d}\n", i, data->points[i].x, data->points[i].y);
		}
		i++;
	}
}
