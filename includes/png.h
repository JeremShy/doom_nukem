#ifndef PNG_H
# define PNG_H

# include <stdint.h>
# include <stddef.h>

# define MAX_BITS 15

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
*/

struct	s_png_ihdr {
	uint32_t	width;
	uint32_t	height;
	uint8_t		bdp;
	uint8_t		color_type;
	uint8_t		compression;
	uint8_t		filter;
	uint8_t		interlace;
};

struct	s_chunk_hdr {
	uint32_t	length;
	uint32_t	type;
};

struct	s_length_code {
	uint8_t	length;
	uint8_t	code;
	char	symbol; // For testing purpose
};

void	*png_inflate(uint8_t *data, size_t datasize);

#endif
