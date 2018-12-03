#include <editor.h>
#include <png.h>



void	*png_inflate(uint8_t *data, size_t datasize)
{
	(void)datasize;
	uint8_t					cmf;
	uint8_t					*compressed_data;
	struct s_length_code	length_code[] = {{3, 0, 'A'}, {3, 0, 'B'}, {3, 0, 'C'}, {3, 0, 'D'}, {3, 0, 'E'}, {2, 0, 'F'}, {1, 0, 'G'}, {4, 0, 'H'}};
	size_t	s = 8;
	uint8_t					*bl_count; //Let bl_count[N] be the number of codes of length N, N >= 1.
	size_t					i;
	size_t					j;

	// Marche pas du tout, faudrait commencer par calculer le code de taille max.

	cmf = data[0];
	printf("cm : %u\n", cmf & 0xf);
	printf("cinfo : %u\n", cmf >> 4);
	printf("flags  : %x\n", data[1]);
	compressed_data = data + 2;

	bl_count = malloc((8 + 1) * sizeof(uint8_t));
	ft_bzero(bl_count, (8 + 1) * sizeof(uint8_t));
	i = 1;
	printf("size : %d\n", 8);
	while (i <= 8)
	{
		j = 0;
		while (j < 8)
		{
			if (length_code[j].length == i)
				bl_count[i]++;
			j++;
		}
		i++;
	}
	i = 1;
	while (i <= 8)
	{
		printf("bl_count[%zu] = %d\n", i, bl_count[i]);
		i++;
	}
	return (NULL);
}