#include <editor.h>

float		get_idist(const t_ivec2 *p1, const t_ivec2 *p2)
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

uint32_t	min(uint32_t a, uint32_t b)
{
	return (a < b ? a : b);
}

uint32_t	max(uint32_t a, uint32_t b)
{
	return (a > b ? a : b);
}
