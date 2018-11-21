#include <game.h>

uint32_t	invert_transparency(uint32_t c)
{
	int	alpha;

	alpha = c >> 24;
	alpha = 255 - (uint8_t)alpha;
	return (alpha << 24 | (c & 0x00ffffff));
}

uint32_t	*parse_tga(char *name, t_tga_header *header)
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
	printf("je suis ici\n");
	if (header->id_length != 0 || header->color_map_type != 0 || header->image_type != 2
		|| ft_memcmp(header->color_map_spec, "\0\0\0\0\0", 5) != 0)
	{
		dprintf(2, "Error : tga file not handled.\n");
		return (NULL);
	}
	img_data = addr + sizeof(t_tga_header);
	return (img_data);
}
