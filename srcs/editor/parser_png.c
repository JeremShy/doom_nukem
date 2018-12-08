#include <editor.h>
#include <png.h>

void		*init_png_parser(const char *name, off_t *size)
{
	int				fd;
	struct stat		buf;
	void			*addr;

	if ((fd = open(name, O_RDONLY)) == -1)
	{
		dprintf(2, "Error : Couldn't open file %s\n", name);
		return (NULL);
	}
	if ((fstat(fd, &buf)) == -1)
	{
		dprintf(2, "Error : Couldn't open file %s\n", name);
		close(fd);
		return (NULL);
	}
	*size = buf.st_size;
	if ((addr = mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		dprintf(2, "Error : Couldn't map file %s\n", name);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (addr);
}

static uint8_t	check_and_read_ihdr(void *addr, struct s_png_ihdr *png_ihdr)
{
	struct s_chunk_hdr	chunk_header;

	chunk_header.length = get_conv_32(addr + 8);
	chunk_header.type = get_conv_32(addr + 12);
	printf("chunk_length : %u\n", chunk_header.length);
	printf("chunk_length : %x\n", chunk_header.type);
	if (chunk_header.type != 0x49484452 || chunk_header.length != 13) // IHDR
	{
		dprintf(2, "Invalid first chunk.\n");
		return (0);
	}
	*png_ihdr = *((struct s_png_ihdr*)(addr + 16));

	png_ihdr->width = get_conv_32(&png_ihdr->width);
	png_ihdr->height = get_conv_32(&png_ihdr->height);

	if (png_ihdr->color_type == 2)
		png_ihdr->bytes_per_pixel = 3 * (png_ihdr->bdp >> 3);
	else if (png_ihdr->color_type == 6)
		png_ihdr->bytes_per_pixel = 4 * (png_ihdr->bdp >> 3);
	else if (png_ihdr->color_type == 0)
		png_ihdr->bytes_per_pixel = (png_ihdr->bdp >> 3);
	else
		png_ihdr->bytes_per_pixel = 0;
	if (png_ihdr->compression != 0 || png_ihdr->filter != 0)
	{
		dprintf(2, "Unknown compression method or unknown filter.\n");
		return (0);
	}
	return (1);
}

struct s_chunk_hdr		*get_next_chunk(void *current_chunk)
{
	struct s_chunk_hdr	*ret;

	ret = current_chunk;
	ret = (void*)ret + get_conv_32(&ret->length) + 12;
	while (get_conv_32(&ret->type) != IEND && (ret->type & 0x20))
		ret = (void*)ret + get_conv_32(&ret->length) + 12;
	return (ret);
}

uint8_t print_and_ret(const char *str, void *addr, off_t file_size, uint8_t *compressed_data)
{
	ft_putendl_fd(str, 2);
	munmap(addr, file_size);
	free(compressed_data);
	return (0);
}

void		copy_source_in_img(t_data *data, struct s_png_ihdr *png_ihdr, int id_img, uint8_t *img_data)
{
	size_t	index_source;
	size_t	index_dest;
	uint32_t	transp;

	index_source = 0;
	index_dest = 0;
	while (index_dest < png_ihdr->width * png_ihdr->height)
	{
		if (index_source % (png_ihdr->width * png_ihdr->bytes_per_pixel + 1) == 0)
			index_source++;
		if (png_ihdr->bytes_per_pixel == 4)
			transp = 255 - img_data[index_source + 3];
		else
			transp = 0;
		if (png_ihdr->bytes_per_pixel == 3 || png_ihdr->bytes_per_pixel == 4)
			data->imgs[id_img].addr[index_dest] = get_color_code(img_data[index_source], img_data[index_source + 1], img_data[index_source + 2], transp);
		else
			data->imgs[id_img].addr[index_dest] = get_color_code(img_data[index_source], img_data[index_source], img_data[index_source], transp);
		index_source += png_ihdr->bytes_per_pixel;
		index_dest++;
	}
}

void		apply_all_filters(struct s_png_ihdr *png_ihdr, uint8_t *img_data)
{
	size_t	index_source;
	size_t	index_dest;
	size_t	source_size;
	uint8_t	current_filter;

	index_source = 0;
	index_dest = 0;
	source_size = png_ihdr->width * png_ihdr->height * png_ihdr->bytes_per_pixel + png_ihdr->height;
	while (index_source < source_size)
	{
		if (index_source % (png_ihdr->width * png_ihdr->bytes_per_pixel + 1) == 0)
		{
			current_filter = img_data[index_source];
			index_source++;
		}
		img_data[index_source] = apply_filter(current_filter, img_data, png_ihdr, index_source, img_data[index_source]);
		index_source++;
	}
}

uint8_t		*get_compressed_data(void *addr, size_t file_size)
{
	size_t				all_idats_size;
	struct s_chunk_hdr	*current_chunk;
	uint8_t				*compressed_data;
	size_t				i;

	all_idats_size = 0;
	current_chunk = addr + 8;
	while (get_conv_32(&(current_chunk = get_next_chunk(current_chunk))->type) != IEND)
	{
		if (get_conv_32(&current_chunk->type) != IDAT)
			return ((void*)(int64_t)print_and_ret("Only IDAT supported", addr, file_size, NULL));
		all_idats_size += get_conv_32(&current_chunk->length);
	}
	if (!(compressed_data = malloc(all_idats_size)))
		return ((void*)(int64_t)print_and_ret("Memory error", addr, file_size, NULL));
	current_chunk = addr + 8;
	i = 0;
	while (get_conv_32(&(current_chunk = get_next_chunk(current_chunk))->type) != IEND)
	{
		ft_memcpy(compressed_data + i, (void*)current_chunk + 8, get_conv_32(&current_chunk->length));
		i += get_conv_32(&current_chunk->length);
	}
	return (compressed_data);
}

uint8_t		initialize_values(void **addr, const char *name, off_t *file_size, struct s_png_ihdr *png_ihdr)
{
	if (!(*addr = init_png_parser(name, file_size)))
		return (0);
	if (*file_size < 8 || get_conv_64(*addr) != 0x89504E470D0A1A0Al)
		return (print_and_ret("Invalid signature", *addr, *file_size, NULL));
	if (!check_and_read_ihdr(*addr, png_ihdr))
		return (print_and_ret("Error", *addr, *file_size, NULL));
	return (1);
}

uint8_t		create_image_from_png(t_data *data, int id_img, const char *name, t_ivec2 *size)
{
	struct s_png_ihdr	png_ihdr;
	void				*addr;
	off_t				file_size;
	uint8_t				*img_data;
	uint8_t				*compressed_data;

	(void)size;
	if (!initialize_values(&addr, name, &file_size, &png_ihdr))
		return (0);
	if (!(compressed_data = get_compressed_data(addr, file_size)))
		return (0);
	munmap(addr, file_size);
	if (!(img_data = malloc(png_ihdr.width * png_ihdr.height *
		png_ihdr.bytes_per_pixel+ png_ihdr.height)))
		return (print_and_ret("Memory error 2", NULL, file_size,
			compressed_data));
	png_inflate((void*)compressed_data, img_data);
	free(compressed_data);
	create_image(data, id_img, png_ihdr.width, png_ihdr.height);
	apply_all_filters(&png_ihdr, img_data);
	copy_source_in_img(data, &png_ihdr, id_img, img_data);
	free(img_data);
	return (1);
}


/*	On a : RGBA
	On veut : ARGB
*/

// BGRA
// RGBA
// 
