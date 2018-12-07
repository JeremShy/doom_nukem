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

uint16_t		get_next_symbol(uint8_t *data, size_t datasize, uint8_t *current_bit, uint32_t *current_byte, struct s_tree *tree)
{
	uint8_t	bit;

	while (tree->l || tree->r)
	{
		bit = read_n_bits(data, current_bit, current_byte, 1);
		if (!bit)
			tree = tree->l;
		else
			tree = tree->r;
	}
	// ft_printf("\n");
	return (tree->symbol);
}

void	get_error(struct s_length_code *len, uint16_t nbr)
{
	float		err;
	int			i;
	uint16_t	bl_count[MAX_BITS + 1];

	ft_bzero(bl_count, sizeof(bl_count));
	err = 0;
	i = 1;
	fill_bl_count(bl_count, len, nbr);
	while (i <= MAX_BITS)
	{
		err += (float)(bl_count[i]) / (1 << i);
		i++;
	}
	if (err > 1.001 || err < 0.99)
	{
		printf("Erreur dans le tableau %f\n", err);
		// exit(0);
	}
}

void			write_lenght_code(struct s_length_code *len, uint16_t
	occurency, size_t *index_in_len, uint16_t sym)
{
	size_t		i;

	i = 0;
	while (i < occurency)
	{
		if (sym == 16)
			len[*index_in_len] = (struct s_length_code){
				len[*index_in_len - 1].length, 0, *index_in_len};
		else
			len[*index_in_len] = (struct s_length_code){0, 0, *index_in_len};
		(*index_in_len)++;
		i++;
	}
}

static void		get_len_list(uint8_t *data, size_t datasize,
	uint8_t *current_bit, uint32_t *current_byte, 
	struct s_length_code *len, uint16_t nbr, struct s_tree *a)
{
	size_t		index_in_len;
	uint16_t	sym;

	index_in_len = 0;
	while (index_in_len < nbr)
	{
		sym = get_next_symbol(data, datasize, current_bit, current_byte, a);
		if (sym <= 15)
		{
			len[index_in_len] = (struct s_length_code){sym, 0, index_in_len};
			index_in_len++;
		}
		else if (sym == 16)
			write_lenght_code(len, 3 + read_n_bits(data,
				current_bit, current_byte, 2), &index_in_len, sym);
		else if (sym == 17)
			write_lenght_code(len, 3 + read_n_bits(data,
				current_bit, current_byte, 3), &index_in_len, sym);
		else if (sym == 18)
			write_lenght_code(len, 11 + read_n_bits(data,
				current_bit, current_byte, 7), &index_in_len, sym);
		else
			exit(printf("Error 132\n"));
	}
	if (index_in_len > nbr)
		printf("wtf\n");
}

uint8_t		process_block(uint8_t *data, size_t datasize)
{
	enum e_compression_method	compression_method;
	uint8_t						current_bit;
	uint32_t					current_byte;
	uint8_t						final;
	uint16_t					hlit;
	uint8_t						hdist;
	uint8_t						hclen;
	size_t						i;
	size_t						index_in_img;
	size_t						j;
	uint16_t					sym;
	struct s_tree				*a;
	struct s_length_code		a_lens[19];
	struct s_tree				*b;
	struct s_length_code		b_lens[288];
	struct s_tree				*c;
	struct s_length_code		c_lens[32];
	uint16_t					len;
	uint16_t					distance;
	char						*image;

	ft_bzero(a_lens, sizeof(a_lens));
	ft_bzero(b_lens, sizeof(b_lens));
	ft_bzero(c_lens, sizeof(c_lens));

	current_bit = 0;
	current_byte = 0;

	image = malloc(1024 * 1024);
	final = read_n_bits(data, &current_bit, &current_byte, 1);
	compression_method = read_n_bits(data, &current_bit, &current_byte, 2);
	print_compression_method(compression_method);

	if (compression_method == no_compression || compression_method == invalid)
	{
		printf("not handled or invalid.\n");
		return (0);
	}

	if (compression_method == dynamic_huffman)
	{
		hlit = read_n_bits(data, &current_bit, &current_byte, 5) + 257;
		hdist = read_n_bits(data, &current_bit, &current_byte, 5) + 1;
		hclen = read_n_bits(data, &current_bit, &current_byte, 4) + 4;

		printf("hlit : %d\n", hlit);
		printf("hdist : %d\n", hdist);
		printf("hclen : %d\n", hclen);

		i = 0;
		while (i < 19)
		{
			a_lens[g_a_init[i].symbol].symbol = g_a_init[i].symbol;
			if (i < hclen)
				a_lens[g_a_init[i].symbol].length = read_n_bits(data, &current_bit, &current_byte, 3);
			i++;
		}
		get_code_from_lengths(a_lens, 19);
		get_error(a_lens, 19);
		i = 0;
		while (i < 19)
		{
			ft_printf("a_len[%zu] = {%d, %.16b, %d}\n", i, a_lens[i].length, a_lens[i].code, a_lens[i].symbol);
			i++;
		}
		a = create_tree(a_lens, 19);

		get_len_list(data, datasize, &current_bit, &current_byte, b_lens, hlit, a);
		get_error(b_lens, hlit);
		get_code_from_lengths(b_lens, hlit);
		b = create_tree(b_lens, hlit);

		i = 0;
		while (i < hlit)
		{
			ft_printf("b_len[%zu] = {%d, %.16b, %d}\n", i, b_lens[i].length, b_lens[i].code, b_lens[i].symbol);
			i++;
		}

		get_len_list(data, datasize, &current_bit, &current_byte, c_lens, hdist, a);
		get_code_from_lengths(c_lens, hdist);
		c = create_tree(c_lens, hdist);
	}
	else if (compression_method == fixed_huffman)
	{
		i = 0;
		while (i <= 143)
		{
			b_lens[i] = (struct s_length_code){8, 0, i};
			i++;
		}
		while (i <= 255)
		{
			b_lens[i] = (struct s_length_code){9, 0, i};
			i++;
		}
		while (i <= 279)
		{
			b_lens[i] = (struct s_length_code){7, 0, i};
			i++;
		}
		while (i <= 287)
		{
			b_lens[i] = (struct s_length_code){8, 0, i};
			i++;
		}
		get_code_from_lengths(b_lens, 288);
		i = 0;
		while (i < 32)
		{
			c_lens[i] = (struct s_length_code){5, 0, i};
			i++;
		}
		get_code_from_lengths(c_lens, 32);
		b = create_tree(b_lens, 288);
		c = create_tree(c_lens, 32);
	}
	index_in_img = 0;
	sym = 0;
	while (sym != 256)
	{
		sym = get_next_symbol(data, datasize, &current_bit, &current_byte, b);
		printf("sym : %d\n", sym);
		if (sym < 256)
		{
			image[index_in_img] = sym;
			index_in_img++;
		}
		else if (sym > 256)
		{
			len = g_length_codes_base_len[sym - 257][1] + (int)read_n_bits(data, &current_bit, &current_byte, g_length_codes_base_len[sym - 257][0]);
			printf("must read : %d codes (%d extra bits and %d base len)\n", len, g_length_codes_base_len[sym - 257][0], g_length_codes_base_len[sym - 257][1]);
			distance = get_next_symbol(data, datasize, &current_bit, &current_byte, c);
			distance = g_dist_base_len[distance][1] + (int)read_n_bits(data, &current_bit, &current_byte, g_dist_base_len[distance][0]);
			printf("distance : %d\n", distance);
			i = 0;
			while (i < len)
			{
				if (index_in_img + i >= distance)
					image[i + index_in_img] = image[index_in_img - distance + i];
				else
					exit(printf("Error 184\n"));
				i++;
			}
			index_in_img += len;
		}
	}
	write(1, image, index_in_img);
	return (1);
}

void		*png_inflate(uint8_t *data, size_t datasize)
{
	// uint8_t					cmf;
	// uint8_t					*compressed_data;
	// struct s_length_code	length_code[] = {{3, 0, 'A'}, {3, 0, 'B'}, {3, 0, 'C'}, {3, 0, 'D'}, {3, 0, 'E'}, {2, 0, 'F'}, {4, 0, 'G'}, {4, 0, 'H'}};
	// size_t					s;


	// printf("%.*s\n", (int)datasize, data);
	// fwrite(data, 1, datasize, stdout);

	// s = sizeof(length_code) / sizeof(struct s_length_code);
	// cmf = data[0];

	// printf("cm : %u\n", cmf & 0xf);
	// printf("cinfo : %u\n", cmf >> 4);
	// printf("winsize : %u\n", winsize);
	// printf("flags  : %x\n", data[1]);
	// compressed_data = data + 2;

	// get_code_from_lengths(length_code, s);

	printf("compressed_data[0] : %x\n", data[0 + 2]);
	printf("compressed_data[1] : %x\n", data[1 + 2]);
	printf("compressed_data[2] : %x\n", data[2 + 2]);
	printf("compressed_data[3] : %x\n", data[3 + 2]);
	printf("compressed_data[4] : %x\n", data[4 + 2]);



	if (!process_block(data + 2, datasize - 2))
		return (NULL);

	return (NULL);
}
