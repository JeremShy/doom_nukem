#include <editor.h>
#include <png.h>

uint8_t		create_image_from_png(t_data *data, int id_img, const char *name, t_ivec2 *size)
{
	// uint32_t	*img_data;
	int					fd;
	struct stat			buf;
	uint32_t			chunk_header[2];
	struct s_png_ihdr	png_ihdr;
	void				*addr;

	(void)data;
	(void)id_img;
	(void)size;
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
	addr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE | MAP_FILE, fd, 0);
	if (addr == NULL)
	{
		dprintf(2, "map error\n");
		return (0);
	}
	if (get_conv_64(addr) != 0x89504E470D0A1A0Al)
	{
		dprintf(2, "invalid signature.\n");
		return (0);
	}
	chunk_header[0] = get_conv_32(addr + 8);
	chunk_header[1] = get_conv_32(addr + 12);
	printf("chunk_length : %u\n", chunk_header[0]);
	printf("chunk_length : %x\n", chunk_header[1]);
	if (chunk_header[1] != 0x49484452 || chunk_header[0] != 13) // IHDR
	{
		dprintf(2, "Invalid first chunk.\n");
		return (0);
	}
	png_ihdr = *((struct s_png_ihdr*)(addr + 16));
	png_ihdr.width = get_conv_32(&png_ihdr.width);
	png_ihdr.height = get_conv_32(&png_ihdr.height);

	printf("image width : %u\n", png_ihdr.width);
	printf("image height : %u\n", png_ihdr.height);
	printf("bdp : %hhu\n", png_ihdr.bdp);
	printf("color_type : %hhu\n", png_ihdr.color_type);
	printf("compression : %hhu\n", png_ihdr.compression);
	printf("filter : %hhu\n", png_ihdr.filter);
	printf("interlace : %hhu\n", png_ihdr.interlace);

	return (0);
}
