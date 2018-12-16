#include <editor.h>

void	bresenham_quadrant1(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color)
{
	int dp;
	int de;
	int	dne;
	int i;

	i = ((double)(p2.y - p1.y) / ((double)p2.x - p1.x) > 1 ? 0 : 1);
	de = (i ? 2 * (p2.y - p1.y) : 2 * (p2.x - p1.x));
	dp = (i ? 2 * (p2.y - p1.y) - (p2.x - p1.x)
			: 2 * (p2.x - p1.x) - (p2.y - p1.y));
	dne = (i ? 2 * ((p2.y - p1.y) - (p2.x - p1.x))
			: 2 * ((p2.x - p1.x) - (p2.y - p1.y)));
	put_pixel_to_image(img, p1.x, p1.y, color);
	while ((p1.x < p2.x && i == 1) || (p1.y < p2.y && i == 0))
	{
		if (dp <= 0)
			dp = dp + de;
		else
		{
			i ? p1.y++ : p1.x++;
			dp = dp + dne;
		}
		i ? p1.x++ : p1.y++;
		put_pixel_to_image(img, p1.x, p1.y, color);
	}
}

void	bresenham_quadrant2(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color)
{
	int dp;
	int de;
	int	dne;
	int i;

	i = ((double)(p2.y - p1.y) / ((double)p1.x - p2.x) > 1 ? 0 : 1);
	de = (i ? 2 * (p2.y - p1.y) : 2 * (p1.x - p2.x));
	dp = (i ? 2 * (p2.y - p1.y) - (p1.x - p2.x)
			: 2 * (p1.x - p2.x) - (p2.y - p1.y));
	dne = (i ? 2 * ((p2.y - p1.y) - (p1.x - p2.x))
			: 2 * ((p1.x - p2.x) - (p2.y - p1.y)));
	put_pixel_to_image(img, p1.x, p1.y, color);
	while ((p1.x > p2.x && i == 1) || (p1.y < p2.y && i == 0))
	{
		if (dp <= 0)
			dp = dp + de;
		else
		{
			dp = dp + dne;
			i ? p1.y++ : p1.x--;
		}
		i ? p1.x-- : p1.y++;
		put_pixel_to_image(img, p1.x, p1.y, color);
	}
}

void	bresenham_quadrant3(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color)
{
	int dp;
	int de;
	int	dne;
	int i;

	i = ((double)(p1.y - p2.y) / ((double)p2.x - p1.x) > 1 ? 0 : 1);
	de = (i ? 2 * (p1.y - p2.y) : 2 * (p2.x - p1.x));
	dp = (i ? 2 * (p1.y - p2.y) - (p2.x - p1.x)
			: 2 * (p2.x - p1.x) - (p1.y - p2.y));
	dne = (i ? 2 * ((p1.y - p2.y) - (p2.x - p1.x))
			: 2 * ((p2.x - p1.x) - (p1.y - p2.y)));
	put_pixel_to_image(img, p1.x, p1.y, color);
	while ((p1.x < p2.x && i == 1) || (p1.y > p2.y && i == 0))
	{
		if (dp <= 0)
			dp = dp + de;
		else
		{
			dp = dp + dne;
			i ? p1.y-- : p1.x++;
		}
		i ? p1.x++ : p1.y--;
		put_pixel_to_image(img, p1.x, p1.y, color);
	}
}

void	bresenham_quadrant4(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color)
{
	int dp;
	int de;
	int	dne;
	int i;

	i = ((double)(p1.y - p2.y) / ((double)p1.x - p2.x) > 1 ? 0 : 1);
	de = (i ? 2 * (p1.y - p2.y) : 2 * (p1.x - p2.x));
	dp = (i ? 2 * (p1.y - p2.y) - (p1.x - p2.x)
			: 2 * (p1.x - p2.x) - (p1.y - p2.y));
	dne = (i ? 2 * ((p1.y - p2.y) - (p1.x - p2.x))
			: 2 * ((p1.x - p2.x) - (p1.y - p2.y)));
	put_pixel_to_image(img, p1.x, p1.y, color);
	while ((p1.x > p2.x && i == 1) || (p1.y > p2.y && i == 0))
	{
		if (dp <= 0)
			dp = dp + de;
		else
		{
			i ? p1.y-- : p1.x--;
			dp = dp + dne;
		}
		i ? p1.x-- : p1.y--;
		put_pixel_to_image(img, p1.x, p1.y, color);
	}
}
