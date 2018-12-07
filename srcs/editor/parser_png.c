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

	printf("image width : %u\n", png_ihdr->width);
	printf("image height : %u\n", png_ihdr->height);
	printf("bdp : %hhu\n", png_ihdr->bdp);
	printf("color_type : %hhu\n", png_ihdr->color_type);
	printf("compression : %hhu\n", png_ihdr->compression);
	printf("filter : %hhu\n", png_ihdr->filter);
	printf("interlace : %hhu\n", png_ihdr->interlace);
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
	while (get_conv_32(&ret->type) != 0x49454E44 && (ret->type & 0x20))
	{
		printf("Passing chunk : %.4s\n", (char*)&ret->type);
		ret = (void*)ret + get_conv_32(&ret->length) + 12;
	}
	printf("last chunk : %.4s\n", (char*)&ret->type);
	return (ret);
}

uint8_t		create_image_from_png(t_data *data, int id_img, const char *name, t_ivec2 *size)
{
	// uint32_t	*img_data;
	struct s_png_ihdr	png_ihdr;
	void				*addr;
	off_t				file_size;
	struct s_chunk_hdr	*current_chunk;
	uint8_t				*img_data;
	size_t				image_size;
	uint8_t				current_filter;

	(void)data;
	(void)id_img;
	(void)size;
	if (!(addr = init_png_parser(name, &file_size)))
		return (0);
	if (file_size < 8 || get_conv_64(addr) != 0x89504E470D0A1A0Al)
	{
		munmap(addr, file_size);
		dprintf(2, "invalid signature.\n");
		return (0);
	}
	if (!check_and_read_ihdr(addr, &png_ihdr))
	{
		munmap(addr, file_size);
		return (0);
	}
	current_chunk = get_next_chunk(addr + 8);

	printf ("width : %d\n", png_ihdr.width);
	printf ("height : %d\n", png_ihdr.height);
	printf ("bdp : %d\n", png_ihdr.bdp);
	printf ("color_type : %d\n", png_ihdr.color_type);
	printf ("compression : %d\n", png_ihdr.compression);
	printf ("filter : %d\n", png_ihdr.filter);
	printf ("interlace : %d\n", png_ihdr.interlace);
	printf("current_chunk : %.4s\n", (char*)&current_chunk->type);
	if (get_conv_32(&current_chunk->type) != 0x49444154) // IDAT
	{
		ft_putendl_fd("Error : IDAT chunk expected.", 2);
		munmap(addr, file_size);
		return (0);
	}
	image_size = png_ihdr.width * png_ihdr.height * ((png_ihdr.bdp / 8) * (png_ihdr.color_type == 6 ? 4 : 3)) + png_ihdr.height;
	printf("image_size : %zu\n", image_size);
	img_data = malloc(image_size);
	png_inflate((void*)current_chunk + 8, img_data);

	create_image(data, id_img, png_ihdr.width, png_ihdr.height);

	size_t	i = 0;
	size_t	j = 0;
	printf("png_ihdr.width * png_ihdr.height * 4 : %d\n", png_ihdr.width * png_ihdr.height * 4);
	printf("image_size : %zu\n", image_size);
	printf("img_data[0] : %d\n", img_data[0]);
	while (i < image_size)
	{
		if (j % (data->imgs[id_img].w * 4) == 0)
		{
			current_filter = img_data[i];
			i++;
			printf("current_filter : %d\n", current_filter);
		}

		((uint8_t*)data->imgs[id_img].addr)[j] = img_data[i];
		((uint8_t*)data->imgs[id_img].addr)[j] = apply_filter(current_filter, (uint8_t*)data->imgs[id_img].addr, &png_ihdr, j);
		i++;
		j++;
	}
	i = 0;
	uint32_t	tmp;
	while (i < png_ihdr.width * png_ihdr.height)
	{
		tmp = data->imgs[id_img].addr[i];
		tmp = (tmp << 24) | (tmp >> 8);
		data->imgs[id_img].addr[i] = invert_transparency(tmp);
		i++;
	}


	return (1);
}


/*	On a : RGBA
	On veut : ARGB
*/
