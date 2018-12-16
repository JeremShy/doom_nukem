#include <libftmatrices.h>

void	ft_vec3_normalize(t_vec3 *vector)
{
	float	magnitude;

	magnitude = ft_vec3_get_magnitude(*vector);
	vector->x = vector->x / magnitude;
	vector->y = vector->y / magnitude;
	vector->z = vector->z / magnitude;
}
