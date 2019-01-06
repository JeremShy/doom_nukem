#include <lib_doom.h>

t_vec3		calculate_normale_with_angles(float angle_x, float angle_y)
{
	t_mat4x4	rot_x;
	t_mat4x4	rot_y;
	t_vec4		vec;
	t_vec3		normal;

	ft_mat4x4_set_rotation(rot_x, angle_x, (t_vec3){1, 0, 0});
	ft_mat4x4_set_rotation(rot_y, angle_y, (t_vec3){0, 1, 0});

	vec = ft_vec4_init((float[]){0, 0, 1, 0});
	vec = ft_mat4x4_mult_with_vec4(rot_x, vec);
	vec = ft_mat4x4_mult_with_vec4(rot_y, vec);
	normal.x = vec.x;
	normal.y = vec.y;
	normal.z = vec.z;
	return (normal);
}

float		get_dist(const t_vec2 *p1, const t_vec2 *p2)
{
	return (sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2)));
}

void		swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void		fswap(float *a, float *b)
{
	float tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

uint32_t	min(uint32_t a, uint32_t b)
{
	return (a < b ? a : b);
}

uint32_t	max(uint32_t a, uint32_t b)
{
	return (a > b ? a : b);
}

void		sclamp(int16_t *point, int16_t min, int16_t max)
{
	*point < min ? (*point = min) : 0;
	*point > max ? (*point = max) : 0;
}

void		clamp(int32_t *point, int32_t min, int32_t max)
{
	*point < min ? (*point = min) : 0;
	*point > max ? (*point = max) : 0;
}

void		fclamp(float *point, float min, float max)
{
	*point < min ? (*point = min) : 0;
	*point > max ? (*point = max) : 0;
}

int32_t		clamp_value(int32_t value, int32_t min, int32_t max)
{
	if (value < min)
		value = min;
	else if (value > max)
		value = max;
	return (value);
}

float		norme(t_vec2 *v)
{
	return (sqrt(v->x * v->x + v->y * v->y));
}

t_vec2		mult_vect_scalar(t_vec2 *v, float f)
{
	t_vec2	rez;

	rez.x = v->x * f;
	rez.y = v->y * f;
	return (rez);
}

void		normalize(t_vec2 *v)
{
	float	tmp;

	tmp = norme(v);
	v->x = v->x / tmp;
	v->y = v->y / tmp;
}

t_ivec2		vec2_to_ivec2(t_vec2 v)
{
	return ((t_ivec2){v.x, v.y});
}

