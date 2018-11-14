#include <editor.h>

uint32_t		min(uint32_t a, uint32_t b)
{
	return (a < b ? a : b);
}

uint32_t		max(uint32_t a, uint32_t b)
{
	return (a > b ? a : b);
}

void	draw_line(const t_ivec2 *p1, const t_ivec2 *p2, t_img *img, uint32_t color)
{
	uint32_t x;
	uint32_t y;

	y = min(p1->y, p2->y);
	x = min(p1->x, p2->x);
	if (p1->x == p2->x)
	{
		while (y <= (uint32_t)fmax(p1->y, p2->y))
		{
			put_pixel_to_image(img, x, y, color);
			y++;
		}
		return ;
	}
	if (p1->x < p2->x && p1->y <= p2->y)
		bresenham_quadrant1(*p1, *p2, img, color);
	else if (p1->y <= p2->y && p2->x < p1->x)
		bresenham_quadrant2(*p1, *p2, img, color);
	else if (p1->x < p2->x && p2->y <= p1->y)
		bresenham_quadrant3(*p1, *p2, img, color);
	else if (p2->y <= p1->y && p2->x < p1->x)
		bresenham_quadrant4(*p1, *p2, img, color);
}
