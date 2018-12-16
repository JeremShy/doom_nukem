#include <libftmatrices.h>

t_vec4	ft_vec4_init(const float tab[4])
{
	t_vec4	vec;

	vec.x = tab[0];
	vec.y = tab[1];
	vec.z = tab[2];
	vec.w = tab[3];
	return (vec);
}
