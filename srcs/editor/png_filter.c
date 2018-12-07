#include <editor.h>
#include <png.h>

uint8_t	left(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr)
{
	uint8_t	bytes_per_complete_pixel;

	if (png_ihdr->color_type == 2)
		bytes_per_complete_pixel = 3 * (png_ihdr->bdp >> 3);
	else if (png_ihdr->color_type == 6)
		bytes_per_complete_pixel = 4 * (png_ihdr->bdp >> 3);
	else
		bytes_per_complete_pixel = 0;

	if (i < bytes_per_complete_pixel)
		return (0);
	else
		return (data[i - bytes_per_complete_pixel]);
}

uint8_t	prior(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr)
{
	uint8_t	bytes_per_complete_pixel;

	if (png_ihdr->color_type == 2)
		bytes_per_complete_pixel = 3 * (png_ihdr->bdp >> 3);
	else if (png_ihdr->color_type == 6)
		bytes_per_complete_pixel = 4 * (png_ihdr->bdp >> 3);
	else
		bytes_per_complete_pixel = 0;

	if (i < bytes_per_complete_pixel * png_ihdr->width)
		return (0);
	else
		return (data[i - (bytes_per_complete_pixel * png_ihdr->width)]);
}

uint8_t	prior_left(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr)
{
	uint8_t	bytes_per_complete_pixel;

	if (png_ihdr->color_type == 2)
		bytes_per_complete_pixel = 3 * (png_ihdr->bdp >> 3);
	else if (png_ihdr->color_type == 6)
		bytes_per_complete_pixel = 4 * (png_ihdr->bdp >> 3);
	else
		bytes_per_complete_pixel = 0;

	if (i < bytes_per_complete_pixel + (bytes_per_complete_pixel * png_ihdr->width))
		return (0);
	else
		return (data[i - (bytes_per_complete_pixel + (bytes_per_complete_pixel * png_ihdr->width))]);
}

uint8_t	sub(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr)
{
	return (data[i] + left(data, i, png_ihdr));
}

uint8_t	up(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr)
{
	return (data[i] + prior(data, i, png_ihdr));
}

// Average(x) + floor((Raw(x-bpp)+Prior(x))/2)
uint8_t	average(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr)
{
	uint16_t	tmp_large;
	uint8_t		tmp;

	tmp_large = left(data, i, png_ihdr) + prior(data, i, png_ihdr);
	tmp = (uint8_t)floor((float)tmp_large / 2.f);
	return (data[i] + tmp);
}

uint8_t	paeth_predictor(uint8_t a, uint8_t b, uint8_t c)
{
	int	p;
	int	pa;
	int	pb;
	int	pc;

	p = a + b - c;
	pa = abs(p - a);
	pb = abs(p - b);
	pc = abs(p - c);
	if (pa <= pb && pa <= pc)
		return (a);
	else if (pb <= pc)
		return (b);
	else
		return (c);
}

uint8_t	paeth(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr)
{
	int	rez;

	rez = data[i] + paeth_predictor(left(data, i, png_ihdr), prior(data, i, png_ihdr), prior_left(data, i, png_ihdr));
	return (rez);
}

uint8_t	apply_filter(uint8_t filter, uint8_t *data, struct s_png_ihdr *png_ihdr, size_t i)
{
	if (filter == 0)
		return (data[i]);
	else if (filter == 1)
		return (sub(data, i, png_ihdr));
	else if (filter == 2)
		return (up(data, i, png_ihdr));
	else if (filter == 3)
		return (average(data, i, png_ihdr));
	else if (filter == 4)
		return (paeth(data, i, png_ihdr));
	else // filter not yet handled
		return (0);
}
