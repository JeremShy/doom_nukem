#include <libftmatrices.h>

t_vec3	ft_vec3_sub(const t_vec3 v1, const t_vec3 v2)
{
	t_vec3	dst;

	dst.x = v1.x - v2.x;
	dst.y = v1.y - v2.y;
	dst.z = v1.z - v2.z;
	return (dst);
}
