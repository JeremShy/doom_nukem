#ifndef PNG_H
# define PNG_H

# include <stdint.h>
# include <stddef.h>
# include <sys/stat.h>

# define MAX_BITS 15

# define IHDR 0x49484452
# define IDAT 0x49444154
# define IEND 0x49454E44

/*
**
** In other words, if one were to print out the compressed data as
** a sequence of bytes, starting with the first byte at the
** *right* margin and proceeding to the *left*, with the most-
** significant bit of each byte on the left as usual, one would be
** able to parse the result from right to left, with fixed-width
** elements in the correct MSB-to-LSB order and Huffman codes in
** bit-reversed order (i.e., with the first bit of the code in the
** relative LSB position).
**
** explications :
** Si on ecrivait une sequence de bytes de droite a gauche, bytes par bytes, avec les bits places "normalement" (bits le plus signifiants en premier) :
** 31 30 29 28 27 26 25 24		...		15 14 13 12 11 10 09 08		07 06 05 04 03 02 01 00
**										^
**										|
**										+ ------- Cet octet sera un huffman code
**
** Alors en le lisant de droite a gauche bits par bits, et en inversant uniquement les huffman codes on aurait le resultat encodé correctemnt :
** 00 01 02 03 04 05 06 07		15 14 13 12 11 10 09 08		...		24 25 26 27 28 29 30 31
**								^
**								|
**								+ ------- Inversé car huffman code (dans l'exemple)



16	

111	001





00 01 02 03 04 05 06 07

07 06 05 04 03 02 01 xx		0f 0e 0d 0c 0b 0a 09 08		xx xx xx xx xx xx xx 10


100f0e0d0c0b0a09 0807060504030201

EF CD AB 89
[0] EF
[1] CD

AB 89
[0] AB

7  6  5  4  3  2  1  0
xx xx 01 00 xx xx xx xx
00 00 00 00 xx xx 01 00



xx xx 07 06 05 04 03 02		01 00 xx xx xx ...



xx xx 00 01 02 03 xx xx		xx xx xx xx xx ...
 1  1  1  0  1  1  0  0
 0  0  1  1  0  1  1 

*/

struct	s_png_ihdr {
	uint32_t	width;
	uint32_t	height;
	uint8_t		bdp;
	uint8_t		color_type;
	uint8_t		compression;
	uint8_t		filter;
	uint8_t		interlace;
	uint8_t		bpp;
};

struct	s_chunk_hdr {
	uint32_t	length;
	uint32_t	type;
};

struct	s_length_code {
	uint8_t		length;
	uint16_t	code;
	uint16_t	symbol; // For testing purpose
};

enum	e_compression_method {
	no_compression = 0,
	fixed_huffman = 1,
	dynamic_huffman = 2,
	invalid = 3
};

struct	s_tree
{
	struct s_tree	*l;
	struct s_tree	*r;
	uint16_t		symbol;
};

struct	s_huff_decode
{
	struct	s_tree*			tree;
	struct	s_length_code*	len;
	uint16_t				size;
};

struct	s_bit_and_byte
{
	uint8_t		*data;
	uint8_t		bit;
	uint32_t	byte;
};

struct	s_png_img
{
	size_t	*index;
	uint8_t	*data;
};

void			get_code_from_lengths(struct s_length_code *length_codes, size_t s);
void			*png_inflate(uint8_t *data, uint8_t *dst);
struct s_tree	*create_tree(struct s_length_code *codes, size_t s);
void			delete_tree(struct s_tree	*tree);


void				*init_png_parser(const char *name, off_t *size);
struct s_chunk_hdr	*get_next_chunk(void *current_chunk);
int64_t				print_and_ret(const char *str, void *addr, off_t file_size, uint8_t *compressed_data);
uint8_t				check_and_read_ihdr(void *addr, struct s_png_ihdr *png_ihdr);

uint8_t				apply_filter(uint8_t filter, uint8_t *data, struct s_png_ihdr *png_ihdr, size_t i);

void		create_fixed_huffman(struct s_huff_decode *b, struct s_huff_decode *c);
void		create_dynamic_huffman(struct s_huff_decode *b, struct s_huff_decode *c, uint8_t *data, struct s_bit_and_byte *current);

uint64_t		read_n_bits(uint8_t *data, struct s_bit_and_byte *current, size_t len);
uint16_t		get_next_symbol(uint8_t *data, struct s_bit_and_byte *current, struct s_tree *tree);
uint8_t			init_png_value(struct s_bit_and_byte	*current, struct s_huff_decode *b, struct s_huff_decode *c, uint8_t *final);
void			get_len_list(uint8_t *data, struct s_bit_and_byte *current, struct s_huff_decode *dst, struct s_tree *a);


uint8_t	left(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr);
uint8_t	prior(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr);
uint8_t	prior_left(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr);
uint8_t	paeth_predictor(int a, int b, int c);

extern const struct s_length_code	g_a_init[19];
extern const int					g_length_codes_base_len[][2];
extern const int					g_dist_base_len[][2];
#endif

// {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
