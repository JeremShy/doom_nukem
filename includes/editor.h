#ifndef EDITOR_H
# define EDITOR_H

# include <doom_nukem.h>

# define WIN_SIZE_X 1600
# define WIN_SIZE_Y 900 // /!\ Can't modify

# define IMAGE_TEST 0

# define MAX_IMAGE (IMAGE_TEST + 1)

# define MAX_POLYGON_NBR 4096
# define MAX_POLYGON_EDGES 64

struct			s_data;
struct			s_polygon;

typedef enum	e_wall
{
	SOLID,
	PORTAL
}				t_wall;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlx;

typedef void (*on_click_func)(struct s_data *data, int id);

typedef struct	s_img
{
	void		*ptr;
	int			w;
	int			h;
	uint32_t	*addr;
}				t_img;

typedef struct	s_polygon
{
	uint32_t		id;
	t_wall			type;
	uint8_t			clickable;
	uint8_t			existing;
	uint32_t		num_edges;
	t_ivec2			edges[MAX_POLYGON_EDGES];
	on_click_func	func;
}				t_polygon;

typedef struct	s_data
{
	t_mlx		mlx;

	t_img		imgs[MAX_IMAGE];


	int			nb_params;
	t_polygon	params[MAX_POLYGON_NBR];
}				t_data;


int	loop_hook(t_data *data);
int	mouse_hook(int button, int x,int y, t_data *data);

void	clicked_polygon(t_data *data, int id);
int8_t	is_in_polygon(int x, int y, t_polygon rect);

uint32_t	get_color_code(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void	put_pixel_to_image(t_img *img, int x, int y, uint32_t color);
void	fill_img(t_img *img, uint32_t color);


void	bresenham_quadrant1(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);
void	bresenham_quadrant2(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);
void	bresenham_quadrant3(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);
void	bresenham_quadrant4(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);
void	draw_line(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);

#endif
