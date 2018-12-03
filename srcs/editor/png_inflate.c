#include <editor.h>
#include <png.h>

void	*png_inflate(uint8_t *data, size_t datasize)
{
	uint8_t	cmf;

	cmf = data[0];
	printf("cm : %u\n", cmf & 0xf);
	printf("cinfo : %u\n", cmf >> 4);
	printf("flags  : %x\n", data[1]);
	return (NULL);
}