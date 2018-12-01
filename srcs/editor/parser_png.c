#include <png.h>

uint8_t		create_image_from_png(t_data *data, int id_img, const char *name, t_ivec2 *size)
{
	uint32_t	*img_data;
	int			fd;
	struct stat	buf;

	if ((fd = open(name, O_RDONLY)) == -1)
	{
		dprintf(2, "Error : Couldn't open file %s\n", name);
		return (0);
	}
	if ((fstat(fd, &buf)) == -1)
	{
		dprintf(2, "Error : Couldn't open file %s\n", name);
		return (0);
	}
	void *addr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE | MAP_FILE, fd, 0);
	if (addr == NULL)
	{
		printf("map error\n");
		return (0);
	}
	if (get_conv_64(addr) != 0x89504E470D0A1A0Al)
	{
		printf("invalid signature.\n");
		return (0);
	}
}
