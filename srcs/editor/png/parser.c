#include <editor.h>
#include <png.h>

static void		copy_source_in_img(struct s_png_ihdr *png_ihdr,
	uint8_t *src_img, uint32_t *dest_img)
{
	size_t		id_source;
	size_t		id_dest;

	id_source = 0;
	id_dest = 0;
	while (id_dest < png_ihdr->width * png_ihdr->height)
	{
		if (id_source % (png_ihdr->width * png_ihdr->bpp + 1) == 0)
			id_source++;
		if (png_ihdr->bpp == 4)
			dest_img[id_dest] = get_color_code(src_img[id_source],
				src_img[id_source + 1], src_img[id_source + 2],
				255 - src_img[id_source + 3]);
		if (png_ihdr->bpp == 3)
			dest_img[id_dest] = get_color_code(src_img[id_source],
				src_img[id_source + 1], src_img[id_source + 2], 0);
		if (png_ihdr->bpp == 2)
			dest_img[id_dest] = get_color_code(src_img[id_source],
				src_img[id_source], src_img[id_source], 0);
		id_source += png_ihdr->bpp;
		id_dest++;
	}
}

static void		apply_all_filters(struct s_png_ihdr *png_ihdr,
	uint8_t *img_data)
{
	size_t	index_source;
	size_t	index_dest;
	size_t	source_size;
	uint8_t	current_filter;

	index_source = 0;
	index_dest = 0;
	source_size = png_ihdr->width * png_ihdr->height * png_ihdr->bpp +
	png_ihdr->height;
	while (index_source < source_size)
	{
		if (index_source % (png_ihdr->width * png_ihdr->bpp + 1) == 0)
		{
			current_filter = img_data[index_source];
			index_source++;
		}
		img_data[index_source] = apply_filter(current_filter, img_data,
			png_ihdr, index_source);
		index_source++;
	}
}

static uint8_t	*get_compressed_data(void *addr, size_t file_size)
{
	struct s_chunk_hdr	*current_chunk;
	uint8_t				*compressed_data;
	size_t				i;

	i = 0;
	current_chunk = addr + 8;
	while (get_conv_32(&(current_chunk =
		get_next_chunk(current_chunk))->type) != IEND)
	{
		if (get_conv_32(&current_chunk->type) != IDAT)
			return ((void*)print_and_ret("NOT IDAT", addr, file_size, NULL));
		i += get_conv_32(&current_chunk->length);
	}
	if (!(compressed_data = malloc(i)))
		return ((void*)print_and_ret("Memory error", addr, file_size, NULL));
	current_chunk = addr + 8;
	i = 0;
	while (get_conv_32(&(current_chunk =
		get_next_chunk(current_chunk))->type) != IEND)
	{
		ft_memcpy(compressed_data + i, (void*)current_chunk + 8,
			get_conv_32(&current_chunk->length));
		i += get_conv_32(&current_chunk->length);
	}
	return (compressed_data);
}

static uint8_t	initialize_values(void **addr, const char *name,
	off_t *file_size, struct s_png_ihdr *png_ihdr)
{
	if (!(*addr = init_png_parser(name, file_size)))
		return (0);
	if (*file_size < 8 || get_conv_64(*addr) != 0x89504E470D0A1A0Al)
		return (print_and_ret("Invalid signature", *addr, *file_size, NULL));
	if (!check_and_read_ihdr(*addr, png_ihdr))
		return (print_and_ret("Error", *addr, *file_size, NULL));
	return (1);
}

uint64_t		avrage_color(uint32_t *color, uint32_t nb)
{
	uint64_t rez;

	color[0] /= nb;
	color[1] /= nb;
	color[2] /= nb;
	color[3] /= nb;
	if (color[0] >= 256 || color[1] >= 256 || color[2] >= 256 || color[3] >= 256)
		printf("NB = %d -> 1 : %d - 2 : %d - 3 : %d - 4 : %d\n", nb, color[0], color[1], color[2], color[3]);
	rez  = color[3] << 24;
	rez += color[2] << 16;
	rez += color[1] << 8;
	rez += color[0];
	// printf("rez = %x\n", rez);
	return (rez);
}

uint64_t		get_color_pixel(uint8_t *first_pix, uint32_t w, t_ivec2 inter_x, t_ivec2 inter_y)
{
	uint32_t	c[4];
	int nb;
	int x;
	int y;

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
	return (avrage_color(c, nb));
}

uint32_t		get_pixel_color(t_ivec2 size, uint32_t *src_img, t_vec2 *count, t_vec2 *ratio)
{
	uint32_t	c[4];
	t_ivec2 	inter_x;
	t_ivec2 	inter_y;
	uint64_t	rez;
	uint64_t	rez2;

	inter_x = (t_ivec2){count->x - (ratio->x / 2), count->x + (ratio->x / 2)};
	inter_y = (t_ivec2){count->y - (ratio->y / 2), count->y + (ratio->y / 2)};
	clamp(&inter_x.x, 0, size.x - 1);
	clamp(&inter_x.y, 0, size.x - 1);
	clamp(&inter_y.x, 0, size.y - 1);
	clamp(&inter_y.y, 0, size.y - 1);
	rez = get_color_pixel((uint8_t *)src_img, size.x, inter_x, inter_y);
	return (rez);
}

void			resize_image(struct s_png_ihdr *png_ihdr, uint32_t *dest_img, uint32_t *src_img, t_ivec2 *size)
{
	int32_t		i;
	t_vec2		count;
	t_vec2		ratio;

	i = 0;
	count = (t_vec2){0, 0};
	ratio = (t_vec2){png_ihdr->width / (float)size->x, png_ihdr->height / (float)size->y};
	while (i < size->x * size->y)
	{
		// dest_img[i] = src_img[(int)count.x + (int)(count.y) * png_ihdr->width];
		dest_img[i] = get_pixel_color((t_ivec2){png_ihdr->width, png_ihdr->height}, src_img, &count, &ratio);
		count.x += ratio.x;
		i++;
		if (i % size->x == 0)
		{
			count.x = 0;
			count.y += ratio.y;
		}
	}
}

uint8_t			create_image_from_png(t_data *data, int id_img,
	const char *name, t_ivec2 *size)
{
	struct s_png_ihdr	png_ihdr;
	void				*addr;
	off_t				file_size;
	uint8_t				*img_data;
	uint8_t				*compressed_data;
	uint32_t			*dest_img;

	if (!initialize_values(&addr, name, &file_size, &png_ihdr))
		return (0);
	if (!(compressed_data = get_compressed_data(addr, file_size)))
		return (0);
	munmap(addr, file_size);
	if (!(img_data = malloc(png_ihdr.width * png_ihdr.height *
		png_ihdr.bpp + png_ihdr.height)))
		return (print_and_ret("Memory error 2", NULL, file_size,
			compressed_data));
		png_inflate((void*)compressed_data, img_data);
	free(compressed_data);
	!size ? size = &(t_ivec2){png_ihdr.width, png_ihdr.height} : 0;
	create_image(data, id_img, size->x, size->y);
	apply_all_filters(&png_ihdr, img_data);
	dest_img = malloc(png_ihdr.width * png_ihdr.height * 4);
	copy_source_in_img(&png_ihdr, img_data, dest_img);
	resize_image(&png_ihdr, data->imgs[id_img].addr, dest_img, size);
	free(dest_img);
	free(img_data);
	return (1);
}
