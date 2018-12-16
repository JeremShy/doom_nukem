#ifndef GAME_H
# define GAME_H

# include <doom_nukem.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>

# define WIN_SIZE_X 1600
# define WIN_SIZE_Y 900 // /!\ Can't modify


# define MAX_SECTOR_NBR 256
# define MAX_SECTOR_EDGES 64

# define MAX_TEXTURES 255

# define MAX_POINTS_NBR MAX_SECTOR_NBR * MAX_SECTOR_EDGES

typedef struct s_sector t_sector;

enum				e_edge_type
{
	WALL,
	PORTAL
};

typedef struct		s_img
{
	void		*ptr;
	int			w;
	int			h;
	uint32_t	*addr;
}					t_img;

typedef struct		s_edge
{
	uint16_t			id;
	enum e_edge_type	type;

	t_sector			*next_sector_1;
	t_sector			*next_sector_2;

	t_vec2				*p1;
	t_vec2				*p2;

	uint16_t			texture_up;
	uint16_t			texture_down;
	uint16_t			texture_wall;
}					t_edge;

typedef struct		s_sector
{
	uint16_t			id;

	uint16_t			texture_floor;
	t_vec3				normale_floor;
	int16_t				height_floor;

	uint16_t			texture_ceiling;
	t_vec3				normale_ceiling;
	int16_t				height_ceiling;

	uint32_t			light;

	uint16_t			nb_edges;
	t_edge				*edges[MAX_SECTOR_EDGES];

}					t_sector;

struct				s_player
{
	t_vec2	pos;
};

typedef struct		s_data
{
	t_mlx			mlx;
	t_img			screen;

	t_img			imgs[MAX_TEXTURES];
	uint16_t		nb_imgs;

	t_vec2			size;
	
	struct s_player	player;

	uint32_t		nb_sectors;
	t_sector		*sectors;

	int32_t			nb_edges;
	t_edge			*edges;

	int32_t			nb_points;
	t_vec2			*points;
}					t_data;

/*
** bresenham.c
*/
void			draw_line(const t_ivec2 *p1, const t_ivec2 *p2, t_img *img, uint32_t color);

/*
** bresenham_quadrants.c
*/
void			bresenham_quadrant1(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);
void			bresenham_quadrant2(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);
void			bresenham_quadrant3(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);
void			bresenham_quadrant4(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);

/*
** mlx_loop.c
*/
int					loop(t_data *data);

/*
** mlx_img_func.c
*/
uint32_t			get_color_code(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void				put_pixel_to_image(t_img *img, int x, int y, uint32_t color);
void				fill_img(t_img *img, uint32_t color);

/*
** parse_input.c
*/
uint8_t				parse_map(t_data *data, const char *filename);



#endif
