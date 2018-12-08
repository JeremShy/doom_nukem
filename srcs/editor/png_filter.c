#include <editor.h>
#include <png.h>

uint8_t	left(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr)
{
	if (i % (png_ihdr->bytes_per_pixel * png_ihdr->width + 1) < png_ihdr->bytes_per_pixel + 1)
		return (0);
	else
		return (data[i - png_ihdr->bytes_per_pixel]);
}

uint8_t	prior(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr)
{
	if (i < png_ihdr->bytes_per_pixel * png_ihdr->width + 1)
		return (0);
	else
		return (data[i - (png_ihdr->bytes_per_pixel * png_ihdr->width + 1)]);
}

uint8_t	prior_left(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr)
{
	if (i % (png_ihdr->bytes_per_pixel * png_ihdr->width + 1) < png_ihdr->bytes_per_pixel + 1)
		return (0);
	else if (i < png_ihdr->bytes_per_pixel * png_ihdr->width + 1)
		return (0);
	else
		return (data[i - (png_ihdr->bytes_per_pixel + png_ihdr->bytes_per_pixel * png_ihdr->width + 1)]);
}

uint8_t	sub(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr, uint8_t color)
{
	return (color + left(data, i, png_ihdr));
}

uint8_t	up(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr, uint8_t color)
{
	return (color + prior(data, i, png_ihdr));
}

// Average(x) + floor((Raw(x-bpp)+Prior(x))/2)
uint8_t	average(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr, uint8_t color)
{
	uint16_t	tmp_large;
	uint8_t		tmp;

	tmp_large = left(data, i, png_ihdr) + prior(data, i, png_ihdr);
	
	tmp = tmp_large >> 1;
	return (color + tmp);
}

uint8_t	paeth_predictor(int a, int b, int c)
{
	int32_t	p;
	int32_t	pa;
	int32_t	pb;
	int32_t	pc;

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

/*
   function PaethPredictor (a, b, c)
   begin
        ; a = left, b = above, c = upper left
        p := a + b - c        ; initial estimate
        pa := abs(p - a)      ; distances to a, b, c
        pb := abs(p - b)
        pc := abs(p - c)
        ; return nearest of a,b,c,
        ; breaking ties in order a,b,c.
        if pa <= pb AND pa <= pc then return a
        else if pb <= pc then return b
        else return c
   end
*/


//Paeth(x) + PaethPredictor(Raw(x-bpp), Prior(x), Prior(x-bpp))
uint8_t	paeth(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr, uint8_t color)
{
	uint8_t	rez;

	rez = color + paeth_predictor(left(data, i, png_ihdr), prior(data, i, png_ihdr), prior_left(data, i, png_ihdr));
	return (rez);
}

uint8_t	apply_filter(uint8_t filter, uint8_t *data, struct s_png_ihdr *png_ihdr, size_t i, uint8_t color)
{
	if (filter == 0)
		return (color);
	else if (filter == 1)
		return (sub(data, i, png_ihdr, color));
	else if (filter == 2)
		return (up(data, i, png_ihdr, color));
	else if (filter == 3)
		return (average(data, i, png_ihdr, color));
	else if (filter == 4)
		return (paeth(data, i, png_ihdr, color));
	else // filter not yet handled
		return (0);
}
