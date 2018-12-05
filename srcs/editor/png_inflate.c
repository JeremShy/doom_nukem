#include <editor.h>
#include <png.h>

void		fill_bl_count(uint16_t *bl_count, struct s_length_code *length_code, size_t s)
{
	uint16_t		i;

	ft_bzero(bl_count, (MAX_BITS + 1) * sizeof(uint16_t));
	i = 0;
	while (i < s) // add one per elem to the corresponding length;
	{
		bl_count[length_code[i].length]++;
		i++;
	}
}

void		fill_next_code(uint16_t *next_code, uint16_t *bl_count)
{
	uint16_t	bits;
	uint16_t	code;

	code = 0;
	bits = 1;
	while (bits <= MAX_BITS)
	{
		code = (code + bl_count[bits - 1]) << 1;
		next_code[bits] = code;
		bits++;
	}
}

void		fill_codes(uint16_t *next_code, struct s_length_code *length_codes, size_t s)
{
	size_t	i;

	i = 0;
	while (i < s)
	{
		if (length_codes[i].length != 0)
		{
			length_codes[i].code = next_code[length_codes[i].length];
			next_code[length_codes[i].length]++;
		}
		i++;
	}
}

void		get_code_from_lengths(struct s_length_code *length_codes, size_t s)
{
	uint16_t				bl_count[MAX_BITS + 1]; //Let bl_count[N] be the number of codes of length N, N >= 1.
	uint16_t				next_code[MAX_BITS + 1];

	fill_bl_count(bl_count, length_codes, s);
	fill_next_code(next_code, bl_count);
	fill_codes(next_code, length_codes, s);
}

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

uint8_t		process_block(uint8_t *data, size_t datasize, uint8_t *current_bit, uint32_t *current_byte, uint32_t winsize)
{
	uint8_t						temp;
	enum e_compression_method	compression_method;
	uint8_t						final;


	final = read_n_bits(data, current_bit, current_byte, 1);
	compression_method = read_n_bits(data, current_bit, current_byte, 2);
	print_compression_method(compression_method);
	if (compression_method == no_compression || compression_method == invalid)
	{
		printf("not handled or invalid.\n");
		return (0);
	}
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
