#include <libftmatrices.h>

void	ft_vec2_normalize(t_vec2 *vector)
{
	float	magnitude;

	magnitude = ft_vec2_get_norme(*vector);
	vector->x = vector->x / magnitude;
	vector->y = vector->y / magnitude;
}
