#ifndef GAME_H
# define GAME_H

# include <doom_nukem.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>

typedef struct	s_image_spec
{
	uint16_t	x_origin;
	uint16_t	y_origin;
	uint16_t	width;
	uint16_t	height;
	uint8_t		pixel_depth;
	uint8_t		descriptor;
}				t_image_spec;

typedef struct	s_tga_header
{
	uint8_t			id_length;
	uint8_t			color_map_type;
	uint8_t			image_type;
	uint8_t			color_map_spec[5];
	t_image_spec	image_spec;
}				t_tga_header;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
}				t_mlx;

typedef struct	s_img
{
	void		*ptr;
	int			w;
	int			h;
	uint32_t	*addr;
}				t_img;


void		print_memory(const void *start, size_t size);

#endif
