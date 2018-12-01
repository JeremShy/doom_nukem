#include <editor.h>

uint32_t		end_conv_32(const uint32_t *nbr)
{
	return (uint32_t)((*nbr >> 24) | ((*nbr & 0xFF0000) >> 8) |
		((*nbr & 0xFF00) << 8) | (*nbr << 24));
}

uint64_t	end_conv_64(const uint64_t *nbr)
{
	return (end_conv_32((void*)nbr + 4)
		| (uint64_t)end_conv_32((uint32_t*)nbr) << 32);
}
