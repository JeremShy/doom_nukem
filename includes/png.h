#ifndef PNG_H
# define PNG_H

#include <stdint.h>

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

void	*png_inflate(uint8_t *data, size_t datasize);

#endif