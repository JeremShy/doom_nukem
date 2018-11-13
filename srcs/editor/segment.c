#include <editor.h>

uint8_t	interval_intersect(uint32_t a1, uint32_t a2, uint32_t b1, uint32_t b2)
{
	uint32_t mini;
	uint32_t maxi;

	mini = min(a1, a2);
	maxi = max(b1, b2);
	if (b1 < mini && b2 < mini)
		return (0);
	if (b1 > maxi && b2 > maxi)
		return (0);
	return (1);
}

void swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

uint8_t	is_intersect(t_ivec2 a1, t_ivec2 a2, t_ivec2 b1, t_ivec2 b2)
{
	float ma;
	float mb;
	float ka;
	float kb;
	float x;

	if (a1.x == a2.x || b1.x == b2.x)
	{
		swap(&a1.x, &a1.y);
		swap(&a2.x, &a2.y);
		swap(&b1.x, &b1.y);
		swap(&b2.x, &b2.y);
	}
	ma = ((float)a1.y - a2.y) / (a1.x - a2.x);
	mb = ((float)b1.y - b2.y) / (b1.x - b2.x);
	ka = a1.y - a1.x * ma;
	kb = b1.y - b1.x * mb;

	printf("ma : %f\nka : %f\nmb : %f\nkb : %f\n", ma, ka, mb, kb);

	if (ma == mb)
		return (interval_intersect(a1.x, a2.x, b1.x, b2.x));
	x = (ka - kb) / (mb - ma);
	printf("x = %f\n", x);
	if (x < min(a1.x, a2.x) || x > max(a1.x, a2.x)
		|| x < min(b1.x, b2.x) || x > max(b1.x, b2.x))
		return (0);
	else
		return (1);
}
