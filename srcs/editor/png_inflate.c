#include <editor.h>
#include <png.h>

uint64_t	read_n_bits(uint8_t *data, uint8_t *current_bit, uint32_t *current_byte, size_t len)
{
	uint64_t	ret;
	size_t		n;
	uint8_t		start_bit;

	ret = 0;
	n = len;
	start_bit = *current_bit;
	while (n)
	{
		ret |= ((data[*current_byte] >> *current_bit) & ((1 << n) - 1)) << (len - n);
		n = (n < 8 - *current_bit ? 0 : (n - (8 - *current_bit)));
		*current_bit = (start_bit + len - n) % 8;
		if (*current_bit == 0)
			(*current_byte)++;
	}
	return (ret);
}

void		print_compression_method(enum e_compression_method m)
{
	if (m == no_compression)
		printf("no compression\n");
	else if (m == fixed_huffman)
		printf("fixed_huffman\n");
	else if (m == dynamic_huffman)
		printf("dynamic huffman\n");
	else if (m == invalid)
		printf("invalid\n");
}

// Tree A : Le code qui permet de decoder les deux autres codes
// Tree B : Literal/Length
// Tree C : Distances

uint8_t		process_block(uint8_t *data, size_t datasize, uint8_t *current_bit, uint32_t *current_byte, uint32_t winsize)
{
	enum e_compression_method	compression_method;
	uint8_t						final;
	uint16_t					hlit;
	uint8_t						hdist;
	uint8_t						hclen;
	struct s_length_code		a_lens[19];
	size_t						i;


	final = read_n_bits(data, current_bit, current_byte, 1);
	compression_method = read_n_bits(data, current_bit, current_byte, 2);
	print_compression_method(compression_method);
	if (compression_method == no_compression || compression_method == invalid)
	{
		printf("not handled or invalid.\n");
		return (0);
	}
	hlit = read_n_bits(data, current_bit, current_byte, 5) + 257;
	hdist = read_n_bits(data, current_bit, current_byte, 5) + 1;
	hclen = read_n_bits(data, current_bit, current_byte, 4) + 4;

	printf("hlit : %d\n", hlit);
	printf("hdist : %d\n", hdist);
	printf("hclen : %d\n", hclen);

	ft_memcpy(a_lens, (struct s_length_code[]){{0, 0, 16}, {0, 0, 17}, {0, 0, 18}, {0, 0, 0}, {0, 0, 8}, {0, 0, 7}, {0, 0, 9}, {0, 0, 6}, {0, 0, 10}, {0, 0, 5}, {0, 0, 11}, {0, 0, 4}, {0, 0, 12}, {0, 0, 3}, {0, 0, 13}, {0, 0, 2}, {0, 0, 14}, {0, 0, 1}, {0, 0, 15}}, 76);
	i = 0;
	while (i < hclen)
	{
		a_lens[i].length = read_n_bits(data, current_bit, current_byte, 3);
		i++;
	}
	get_code_from_lengths(a_lens, 19);
	i = 0;
	while (i < 18)
	{
		if (a_lens[i].length != 0)
			ft_printf("%2d -> %2d -> %.8b | %d\n", a_lens[i].symbol, a_lens[i].length, a_lens[i].code, a_lens[i].code);
		i++;
	}
	struct s_tree *a = create_tree(a_lens, hclen);
	return (1);
}

void		*png_inflate(uint8_t *data, size_t datasize)
{
	(void)datasize;
	uint8_t					cmf;
	uint8_t					*compressed_data;
	struct s_length_code	length_code[] = {{3, 0, 'A'}, {3, 0, 'B'}, {3, 0, 'C'}, {3, 0, 'D'}, {3, 0, 'E'}, {2, 0, 'F'}, {4, 0, 'G'}, {4, 0, 'H'}};
	size_t					s;
	uint32_t				winsize;
	uint8_t					current_bit;
	uint32_t				current_byte;


	s = sizeof(length_code) / sizeof(struct s_length_code);
	cmf = data[0];
	winsize = 2 << ((cmf >> 4) + 7);

	printf("cm : %u\n", cmf & 0xf);
	printf("cinfo : %u\n", cmf >> 4);
	printf("winsize : %u\n", winsize);
	printf("flags  : %x\n", data[1]);
	compressed_data = data + 2;

	get_code_from_lengths(length_code, s);

	printf("compressed_data[0] : %x\n", compressed_data[0]);
	printf("compressed_data[1] : %x\n", compressed_data[1]);
	printf("compressed_data[2] : %x\n", compressed_data[2]);
	printf("compressed_data[3] : %x\n", compressed_data[3]);
	printf("compressed_data[4] : %x\n", compressed_data[4]);

	current_bit = 0;
	current_byte = 0;

	if (!process_block(compressed_data, datasize - 2, &current_bit, &current_byte, winsize))
		return (NULL);

	return (NULL);
}
