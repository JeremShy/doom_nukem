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
	delete_tree(a.tree);
}

void write_from_len_and_dist(uint8_t *data, uint16_t sym, struct s_bit_and_byte *current, size_t *index_in_img, uint8_t *image, struct s_huff_decode c)
{
	uint16_t					len;
	uint16_t					distance;
	size_t						i;

	len = g_length_codes_base_len[sym - 257][1] + (int)read_n_bits(data, current, g_length_codes_base_len[sym - 257][0]);
	distance = get_next_symbol(data, current, c.tree);
	distance = g_dist_base_len[distance][1] + (int)read_n_bits(data, current, g_dist_base_len[distance][0]);
	i = 0;
	while (i < len)
	{
		if (*index_in_img + i >= distance)
			image[i + *index_in_img] = image[*index_in_img - distance + i];
		else
			exit(printf("Error 184\n"));
		i++;
	}
	*index_in_img += len;
}

uint8_t		init_png_value(uint8_t *data, struct s_bit_and_byte	*current, struct s_huff_decode *b, struct s_huff_decode *c, uint8_t *final)
{
	enum e_compression_method	compression_method;

	b->len = malloc(sizeof(struct s_length_code) * 288);
	c->len = malloc(sizeof(struct s_length_code) * 32);
	ft_bzero(b->len, sizeof(struct s_length_code) * 288);
	ft_bzero(c->len, sizeof(struct s_length_code) * 32);
	*final = read_n_bits(data, current, 1);
	compression_method = read_n_bits(data, current, 2);
	if (compression_method == no_compression || compression_method == invalid)
	{
		printf("not handled or invalid. %d\n", compression_method);
		return (0);
	}

	if (compression_method == dynamic_huffman)
		create_dynamic_huffman(b, c, data, current);
	else if (compression_method == fixed_huffman)
		create_fixed_huffman(b, c);
	return (1);
}

uint8_t		process_block(uint8_t *data, uint8_t *image, size_t *index_in_img, struct s_bit_and_byte *current)
{
	uint16_t					sym;
	struct s_huff_decode		b;
	struct s_huff_decode		c;
	uint8_t						final;

	init_png_value(data, current, &b, &c, &final);
	sym = 0;
	while (sym != 256)
	{
		sym = get_next_symbol(data, current, b.tree);
		if (sym < 256)
		{
			image[*index_in_img] = sym;
			(*index_in_img)++;
		}
		else if (sym > 256)
			write_from_len_and_dist(data, sym, current, index_in_img, image, c);
	}
	delete_tree(b.tree);
	delete_tree(c.tree);
	free(b.len);
	free(c.len);
	return (final);
}

void		*png_inflate(uint8_t *data, uint8_t *dst)
{
	size_t						index_in_img;
	struct s_bit_and_byte		current;

	index_in_img = 0;
	current.bit = 0;
	current.byte = 0;
	while (!process_block(data + 2, dst, &index_in_img, &current))
		;
	printf("last index : %zu\n", index_in_img);
	return (NULL);
}
