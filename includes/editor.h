#ifndef EDITOR_H
# define EDITOR_H

# include <doom_nukem.h>

# define WIN_SIZE_X 1600
# define WIN_SIZE_Y 900 // /!\ Can't modify

# define IMAGE_TEST 0

# define MAX_IMAGE (IMAGE_TEST + 1)

# define MAX_ELEMENT_NBR 4096
# define MAX_POLYGON_EDGES 10

struct			s_data;
struct			s_element;
typedef void (*t_on_click_func)(struct s_data *data, uint16_t id);

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

typedef enum	e_elem_type
{
	WALL,
	BUTTON
}				t_elem_type;

typedef enum	e_edge_type
{
	SOLID,
	PORTAL,
	UI
}				t_edge_type;

typedef struct	s_edge
{
	t_edge_type	type;

	uint16_t	id_texture;
}				t_edge;

typedef struct	s_polygon
{
	uint32_t		nb_points;
	uint8_t			finished;

	t_ivec2			points[MAX_POLYGON_EDGES];
	t_edge			edges[MAX_POLYGON_EDGES];
}				t_polygon;

typedef struct	s_element
{
	uint8_t			enabled;
	uint16_t		id;

	t_elem_type		type;

	uint8_t			printable;
	uint8_t			id_texture;

	uint8_t			clickable;
	t_on_click_func	on_click_func;

	t_polygon		polygon;
}				t_element;

typedef struct	s_input
{
	uint16_t	id_texture;
	t_edge_type	wall_type;
}				t_input;

typedef struct	s_data
{
	t_mlx		mlx;

	t_img		imgs[MAX_IMAGE];

	t_input		input;

	int			nb_elements;
	t_element	elements[MAX_ELEMENT_NBR];
}				t_data;


int	loop_hook(t_data *data);
int	mouse_hook(int button, int x,int y, t_data *data);

void	clicked_polygon(t_data *data, int id);
int8_t	is_in_polygon(int x, int y, t_element rect);

uint32_t	get_color_code(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void	put_pixel_to_image(t_img *img, int x, int y, uint32_t color);
void	fill_img(t_img *img, uint32_t color);

uint32_t	min(uint32_t a, uint32_t b);
uint32_t	max(uint32_t a, uint32_t b);

void	bresenham_quadrant1(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);
void	bresenham_quadrant2(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);
void	bresenham_quadrant3(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);
void	bresenham_quadrant4(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);
void	draw_line(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);

t_polygon	draw_edge(t_data *data, t_ivec2 new_point);
uint8_t		is_intersect(t_ivec2 a1, t_ivec2 a2, t_ivec2 b1, t_ivec2 b2);
#endif
