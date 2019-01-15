#include <libftmatrices.h>

static void		fclamp(float *point, float min, float max)
{
	*point < min ? (*point = min) : 0;
	*point > max ? (*point = max) : 0;
}

float			ft_vec2_get_angle(t_vec2 u, t_vec2 v)
{
	float	cos;
	t_vec2	normale;
	int		signe;

	ft_vec2_normalize(&u);
	ft_vec2_normalize(&v);
	cos = ft_vec2_dot(v, u);
	normale = ft_vec2_get_normal(u);
	signe = (ft_vec2_dot(v, normale) > 0 ? 1 : -1);
	fclamp(&cos, -1, 1);
	return (acosf(cos) * signe);
}
