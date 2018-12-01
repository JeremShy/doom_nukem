#include <editor.h>

float		idist(const t_ivec2 *p1, const t_ivec2 *p2)
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
	return (acos(idot_prod(&v1, &v2) / inorm(&v1) / inorm(&v2)));
}

t_ivec2		vec_from_points(const t_ivec2 *p1, const t_ivec2 *p2)
{
	return ((t_ivec2){p2->x - p1->x, p2->y - p1->y});
}
