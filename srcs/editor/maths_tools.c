#include <editor.h>

void		swap(int *a, int *b)
{
	int tmp;

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

t_ivec2		find_middle_edge(t_edge *edge)
{
	return ((t_ivec2){(edge->p1->x + edge->p2->x) / 2, (edge->p1->y + edge->p2->y) / 2});
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
