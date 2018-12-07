#include <editor.h>
#include <png.h>

uint64_t	read_n_bits(uint8_t *data, struct s_bit_and_byte *current, size_t len)
{
	uint64_t	ret;
	size_t		n;
	uint8_t		start_bit;

	ret = 0;
	n = len;
	start_bit = current->bit;
	while (n)
	{
		ret |= ((data[current->byte] >> current->bit) & ((1 << n) - 1)) << (len - n);
		n = (n < 8 - current->bit ? 0 : (n - (8 - current->bit)));
		current->bit = (start_bit + len - n) % 8;
		if (current->bit == 0)
			(current->byte)++;
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

uint16_t		get_next_symbol(uint8_t *data, struct s_bit_and_byte *current, struct s_tree *tree)
{
	uint8_t	bit;

	while (tree->l || tree->r)
	{
		bit = read_n_bits(data, current, 1);
		if (!bit)
			tree = tree->l;
		else
			tree = tree->r;
	}
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
	if (err > 1.001 || err < 0.999)
		printf("Erreur dans le tableau %f\n", err);
}

void			write_length_code(struct s_length_code *len, uint16_t
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

static void		get_len_list(uint8_t *data,
	struct s_bit_and_byte *current,
	struct s_length_code *len, uint16_t nbr, struct s_tree *a)
{
	size_t		index_in_len;
	uint16_t	sym;

	index_in_len = 0;
	while (index_in_len < nbr)
	{
		sym = get_next_symbol(data, current, a);
		if (sym <= 15)
		{
			len[index_in_len] = (struct s_length_code){sym, 0, index_in_len};
			index_in_len++;
		}
		else if (sym == 16)
			write_length_code(len, 3 + read_n_bits(data,
				current, 2), &index_in_len, sym);
		else if (sym == 17)
			write_length_code(len, 3 + read_n_bits(data,
				current, 3), &index_in_len, sym);
		else if (sym == 18)
			write_length_code(len, 11 + read_n_bits(data,
				current, 7), &index_in_len, sym);
		else
			exit(printf("Error 132\n"));
	}
}

static void		create_fixed_huffman(struct s_huff_decode *b, struct s_huff_decode *c)
{
	int16_t i;

	i = -1;
	while (++i <= 143)
		b->len[i] = (struct s_length_code){8, 0, i};
	i--;
	while (++i <= 255)
		b->len[i] = (struct s_length_code){9, 0, i};
	i--;
	while (++i <= 279)
		b->len[i] = (struct s_length_code){7, 0, i};
	i--;
	while (++i <= 287)
		b->len[i] = (struct s_length_code){8, 0, i};
	get_code_from_lengths(b->len, 288);
	i = -1;
	while (++i < 32)
		c->len[i] = (struct s_length_code){5, 0, i};
	get_code_from_lengths(c->len, 32);
	b->tree = create_tree(b->len, 288);
	c->tree = create_tree(c->len, 32);
}

static void		create_dynamic_huffman(struct s_huff_decode *b, struct s_huff_decode *c, uint8_t *data, struct s_bit_and_byte *current)
{
	struct s_huff_decode		a;
	struct s_length_code		a_lens[19];
	size_t						i;

	ft_bzero(a_lens, sizeof(a_lens));
	a.len = a_lens;
	b->size = read_n_bits(data, current, 5) + 257;
	c->size = read_n_bits(data, current, 5) + 1;
	a.size = read_n_bits(data, current, 4) + 4;
	i = 0;
	while (i < 19)
	{
		a.len[g_a_init[i].symbol].symbol = g_a_init[i].symbol;
		if (i < a.size)
			a.len[g_a_init[i].symbol].length = read_n_bits(data, current, 3);
		i++;
	}
	get_code_from_lengths(a.len, 19);
	a.tree = create_tree(a.len, 19);
	get_len_list(data, current, b->len, b->size, a.tree);
	get_code_from_lengths(b->len, b->size);
	b->tree = create_tree(b->len, b->size);
	get_len_list(data, current, c->len, c->size, a.tree);
	get_code_from_lengths(c->len, c->size);
	c->tree = create_tree(c->len, c->size);
}

uint8_t		process_block(uint8_t *data)
{
	enum e_compression_method	compression_method;
	struct s_bit_and_byte		current;
	uint8_t						final;
	size_t						i;
	size_t						index_in_img;
	uint16_t					sym;
	struct s_huff_decode		b;
	struct s_huff_decode		c;
	struct s_length_code		b_lens[288];
	struct s_length_code		c_lens[32];
	uint16_t					len;
	uint16_t					distance;
	char						*image;

	ft_bzero(b_lens, sizeof(b_lens));
	ft_bzero(c_lens, sizeof(c_lens));
	b.len = b_lens;
	c.len = c_lens;

	current.bit = 0;
	current.byte = 0;
	image = malloc(1024 * 1024);
	final = read_n_bits(data, &current, 1);
	compression_method = read_n_bits(data, &current, 2);
	print_compression_method(compression_method);

	if (compression_method == no_compression || compression_method == invalid)
	{
		printf("not handled or invalid. %d\n", compression_method);
		return (0);
	}

	if (compression_method == dynamic_huffman)
		create_dynamic_huffman(&b, &c, data, &current);
	else if (compression_method == fixed_huffman)
		create_fixed_huffman(&b, &c);
	index_in_img = 0;
	sym = 0;
	while (sym != 256)
	{
		sym = get_next_symbol(data, &current, b.tree);
		printf("sym : %d\n", sym);
		if (sym < 256)
		{
			image[index_in_img] = sym;
			index_in_img++;
		}
		else if (sym > 256)
		{
			len = g_length_codes_base_len[sym - 257][1] + (int)read_n_bits(data, &current, g_length_codes_base_len[sym - 257][0]);
			printf("must read : %d codes (%d extra bits and %d base len)\n", len, g_length_codes_base_len[sym - 257][0], g_length_codes_base_len[sym - 257][1]);
			distance = get_next_symbol(data, &current, c.tree);
			distance = g_dist_base_len[distance][1] + (int)read_n_bits(data, &current, g_dist_base_len[distance][0]);
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

void		*png_inflate(uint8_t *data)
{
	if (!process_block(data + 2))
		return (NULL);
	return (NULL);
}
