#include <editor.h>

uint32_t	invert_transparency(uint32_t c)
{
	int	alpha;

	alpha = c >> 24;
	alpha = 255 - (uint8_t)alpha;
	return (alpha << 24 | (c & 0x00ffffff));
}

uint32_t	*parse_tga(const char *name, t_tga_header *header)
{
	uint32_t	*img_data;
	int			fd;
	struct stat	buf;

	if ((fd = open(name, O_RDONLY)) == -1)
	{
		dprintf(2, "Error : Couldn't open file %s\n", name);
		return (NULL);
	}
	if ((fstat(fd, &buf)) == -1)
	{
		dprintf(2, "Error : Couldn't open file %s\n", name);
		return (NULL);
	}
	void *addr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE | MAP_FILE, fd, 0);
	if (addr == NULL)
	{
		printf("map error\n");
		return (NULL);
	}
	*header = *(t_tga_header *)addr;
	if (header->id_length != 0 || header->color_map_type != 0 || header->image_type != 2
		|| ft_memcmp(header->color_map_spec, "\0\0\0\0\0", 5) != 0)
	{
		dprintf(2, "Error : tga file not handled.\n");
		return (NULL);
	}
	img_data = addr + sizeof(t_tga_header);
	return (img_data);
}

uint8_t		create_image_from_tga(t_data *data, int id_img, const char *name, t_ivec2 *size)
{
	t_tga_header	header;
	uint32_t		*img;
	t_vec2			ratio;
	int				x;
	int				y;

	if (!(img = parse_tga(name, &header)))
		return (0);
	!size ? size = &(t_ivec2){header.image_spec.width, header.image_spec.height} : 0;
	if (!create_image(data, id_img, size->x, size->y))
		return (0);
	ratio = (t_vec2){(float)header.image_spec.width / size->x, (float)header.image_spec.height / size->y};
	y = 0;
	while (y < size->y)
	{
		x = 0;
		while (x < size->x)
		{
			put_pixel_to_image(&data->imgs[id_img], x, size->y - y - 1, invert_transparency(img[(int)(x * ratio.x) + (int)(y * ratio.y) * header.image_spec.width]));
			x++;
		}
		y++;
	}
	return(1);
}
