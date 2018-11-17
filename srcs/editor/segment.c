#include <editor.h>

static t_intersection	interval_intersect(uint32_t a1, uint32_t a2, uint32_t b1, uint32_t b2)
{
	uint32_t		mini;
	uint32_t		maxi;
	t_intersection	ret;

	// printf("FWEFWFEWW %u - %u - %u - %u\n", a1, a2, b1, b2);
	ret.intersect = 0;
	mini = min(a1, a2);
	maxi = max(a1, a2);
	if (b1 <= mini && b2 <= mini)
		return (ret);
	if (b1 >= maxi && b2 >= maxi)
		return (ret);
	ret.intersect = 1;
	return (ret);
}

// uint8_t			is_common_point(const t_ivec2 *a1, const t_ivec2 *a2, const t_ivec2 *b1, const t_ivec2 *b2)
// {
// 	return (is_equ_ivec2(a1, b1) || is_equ_ivec2(a1, b2) || is_equ_ivec2(a2, b1) || is_equ_ivec2(a2, b2));
// }

// uint8_t					round_inter()
// {
// 		if (x < min(a1.x, a2.x) || x > max(a1.x, a2.x)
// 		|| x < min(b1.x, b2.x) || x > max(b1.x, b2.x))
// 	{
// 		return (ret);
// 	}
// }
t_intersection			is_intersect(t_ivec2 a1, t_ivec2 a2, t_ivec2 b1, t_ivec2 b2)
{
	float			ma; // a
	float			mb;
	float			ka; // b
	float			kb;
	float			x;
	t_intersection	ret;

	ret.intersect = 0;
	if (same_edges(&a1, &a2, &b1, &b2))
		return (ret);
	printf("a1.x = %d, a1.y = %d, a2.x = %d, a2.y = %d, b1.x = %d, b1.y = %d, b2.x = %d, b2.y = %d\n", a1.x, a1.y, a2.x, a2.y, b1.x, b1.y, b2.x, b2.y);
	if (a1.x == a2.x || b1.x == b2.x)
	{
		swap(&a1.x, &a1.y);
		swap(&a2.x, &a2.y);
		swap(&b1.x, &b1.y);
		swap(&b2.x, &b2.y);
	}
	if (a1.x == a2.x)
	{
		if (b1.y <= (int)min(a1.y, a2.y) || b1.y >= (int)max(a1.y, a2.y) || a1.x <= (int)min(b1.x, b2.x) || a1.x >= (int)max(b1.x, b2.x))
			return (ret);
		printf("pouet 1\n");
		ret.intersect = 1;
		ret.intersection_point= (t_ivec2){a1.x, b1.y};
		return (ret);
	}
	else if (b1.x == b2.x)
	{
		if (a1.y <= (int)min(b1.y, b2.y) || a1.y >= (int)max(b1.y, b2.y) || b1.x <= (int)min(a1.x, a2.x) || b1.x >= (int)max(a1.x, a2.x))
			return (ret);
		printf("pouet 2\n");
		ret.intersect = 1;
		ret.intersection_point= (t_ivec2){b1.x, a1.y};
		return (ret);
	}
	ma = ((float)a1.y - a2.y) / (a1.x - a2.x);
	mb = ((float)b1.y - b2.y) / (b1.x - b2.x);
	ka = a1.y - a1.x * ma;
	kb = b1.y - b1.x * mb;

	if (ma == mb)
	{
		if (ka == kb)
		{
			ret = interval_intersect(a1.x, a2.x, b1.x, b2.x);
			printf("pouet 3 %d\n", ret.intersect);
			ret.intersection_point.y = ma * ret.intersection_point.x + ka;
		}
		return (ret);
	}
	x = (ka - kb) / (mb - ma);
	if (x - 0.01 < min(a1.x, a2.x) || x + 0.01 > max(a1.x, a2.x)|| x - 0.01 < min(b1.x, b2.x) || x + 0.01 > max(b1.x, b2.x))
		return (ret);
	printf("Here 123 : %f\n", x);
	ret.intersect = 1;
	ret.intersection_point = (t_ivec2){x, (int)(ma * x + ka)};
	return (ret); 
}
