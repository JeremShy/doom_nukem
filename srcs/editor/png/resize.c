#include <editor.h>
#include <png.h>

static uint64_t	average_color(uint32_t *color, uint32_t nb)
{
	uint64_t rez;

	color[0] /= nb;
	color[1] /= nb;
	color[2] /= nb;
	color[3] /= nb;
	rez = color[3] << 24;
	rez += color[2] << 16;
	rez += color[1] << 8;
	rez += color[0];
	return (rez);
}

static uint64_t	get_color_pixel(uint8_t *first_pix, uint32_t w,
	t_ivec2 inter_x, t_ivec2 inter_y)
{
	uint32_t	c[4];
	int			nb;
	int			x;
	int			y;

	nb = 0;
	ft_bzero(c, sizeof(c));
	x = inter_x.x;
	y = inter_y.x;
	while (y <= inter_y.y)
	{
		c[0] += first_pix[x * 4 + y * 4 * w + 0];
		c[1] += first_pix[x * 4 + y * 4 * w + 1];
		c[2] += first_pix[x * 4 + y * 4 * w + 2];
		c[3] += first_pix[x * 4 + y * 4 * w + 3];
		if (x == inter_x.y)
		{
			x = inter_x.x;
			y++;
		}
		else
			x++;
		nb++;
	}
	return (average_color(c, nb));
}

static uint32_t	get_pixel_color(t_ivec2 size, uint32_t *src_img,
	t_vec2 *count, t_vec2 *ratio)
{
	t_ivec2		inter_x;
	t_ivec2		inter_y;
	uint64_t	rez;

	inter_x = (t_ivec2){roundf(count->x - (ratio->x / 2)),
		roundf(count->x + (ratio->x / 2 - .001))};
	inter_y = (t_ivec2){roundf(count->y - (ratio->y / 2)),
		roundf(count->y + (ratio->y / 2 - .001))};
	clamp(&inter_x.x, 0, size.x - 1);
	clamp(&inter_x.y, 0, size.x - 1);
	clamp(&inter_y.x, 0, size.y - 1);
	clamp(&inter_y.y, 0, size.y - 1);
	rez = get_color_pixel((uint8_t *)src_img, size.x, inter_x, inter_y);
	return (rez);
}

void			resize_image(struct s_png_ihdr *png_ihdr, uint32_t *dest_img,
	uint8_t *img_data, t_ivec2 *size)
{
	int32_t		i;
	t_vec2		count;
	t_vec2		ratio;
	uint32_t	*src_img;

	src_img = malloc(png_ihdr->width * png_ihdr->height * 4);
	copy_source_in_img(png_ihdr, img_data, src_img);
	i = 0;
	count = (t_vec2){0, 0};
	ratio = (t_vec2){png_ihdr->width / (float)size->x, png_ihdr->height
		/ (float)size->y};
	while (i < size->x * size->y)
	{
		dest_img[i] = get_pixel_color((t_ivec2){png_ihdr->width,
			png_ihdr->height}, src_img, &count, &ratio);
		count.x += ratio.x;
		i++;
		if (i % size->x == 0)
		{
			count.x = 0;
			count.y += ratio.y;
		}
	}
	free(src_img);
}
