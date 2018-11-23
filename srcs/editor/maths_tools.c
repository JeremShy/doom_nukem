#include <editor.h>

t_ivec2		vec_from_points(const t_ivec2 *p1, const t_ivec2 *p2)
{
	return ((t_ivec2){p2->x - p1->x, p2->y - p1->y});
}

float		get_idist(const t_ivec2 *p1, const t_ivec2 *p2)
{
	return (sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2)));
}

float		inorm(const t_ivec2 *v1)
{
	return (sqrt(v1->x * v1->x + v1->y * v1->y));
}

int 		idot_prod(const t_ivec2 *v1, const t_ivec2 *v2)
{
	return (v1->x * v2->x + v1->y * v2->y);
}

float		iangle(const t_ivec2 v1, const t_ivec2 v2)
{
	printf("acos(%f) = %f degres\n", idot_prod(&v1, &v2) / inorm(&v1) / inorm(&v2), acos(idot_prod(&v1, &v2) / inorm(&v1) / inorm(&v2)) * 180 / M_PI);
	return (acos(idot_prod(&v1, &v2) / inorm(&v1) / inorm(&v2)));
}

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
