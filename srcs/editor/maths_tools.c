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

