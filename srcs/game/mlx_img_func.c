#include <game.h>

uint32_t	get_color_code(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (((int)b << 0) | ((int)g << 8) | ((int)r << 16) | ((int)a << 24));
}

void	put_pixel_to_image(t_img *img, int x, int y, uint32_t color)
{
	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
	{
		return ;
		// dprintf(2, "Error 12. (put_pixel_to_image)\n");
		// dprintf(2, "{img, x, y, color : {%p, %d, %d, %#X}\n", img, x, y, color);
		// exit(EXIT_FAILURE);
	}
	img->addr[x + y * img->w] = color;
}

void	fill_img(t_img *img, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->w)
	{
		j = 0;
		while (j < img->h)
		{
			put_pixel_to_image(img, i, j, color);
			j++;
		}
		i++;
	}
}
