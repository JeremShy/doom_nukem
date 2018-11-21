#ifndef EDITOR_H
# define EDITOR_H

# include <background_editor.h>
# include <doom_nukem.h>

# define WIN_SIZE_X 1600
# define WIN_SIZE_Y 900 // /!\ Can't modify

# define DRAWING_ZONE_WIDTH 1061

# define IMG_BACKGROUND 0
# define IMG_DRAWING 1

# define MAX_IMAGE (IMG_DRAWING + 1)

# define MAX_ELEMENT_NBR 1024
# define MAX_POLYGON_EDGES 64

# define GRID_ROUND 25

# define MAX_POINTS_NBR MAX_ELEMENT_NBR * MAX_POLYGON_EDGES

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

enum	e_edge_position
{
	BEGIN,
	MIDDLE,
	END
};


enum	e_elem_type
{
	WALL,
	BUTTON
};

enum	e_edge_type
{
	SOLID,
	PORTAL,
	UI
};

enum	e_input_mode
{
	DRAWING,
	SELECTING
};

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

typedef struct	s_intersection
{
	uint8_t		intersect;
	t_ivec2		intersection_point;
}				t_intersection;

typedef struct	s_edge
{
	uint8_t				used;
	enum e_edge_type	type;

	uint16_t			id_texture;
}				t_edge;

typedef struct		s_polygon
{
	uint8_t			nb_points;
	int8_t			finished;

	t_ivec2			*points[MAX_POLYGON_EDGES];
	t_edge			*edges[MAX_POLYGON_EDGES];
}					t_polygon;

typedef struct			s_element
{
	uint16_t			id;

	enum e_elem_type	type;

	uint8_t				printable;
	uint8_t				id_texture;

	uint8_t				clickable;
	uint8_t				enabled;
	t_on_click_func		on_click_func;

	t_polygon			polygon;
}						t_element;

typedef struct	s_input
{
	uint16_t			id_texture;
	enum e_edge_type	wall_type;
	int32_t				id_current_element;
	enum e_input_mode	input_mode;
}				t_input;

typedef struct	s_data
{
	t_mlx		mlx;

	t_img		imgs[MAX_IMAGE];

	t_input		input;

	uint32_t	nb_elements;
	t_element	elements[MAX_ELEMENT_NBR];

	t_edge		edges[MAX_POINTS_NBR];

	t_ivec2		points[MAX_POINTS_NBR];
	uint8_t		used_point[MAX_POINTS_NBR];
}				t_data;

int				loop_hook(t_data *data);
int				mouse_hook(int button, int x,int y, t_data *data);
int				key_hook(int keycode, t_data *data);

uint32_t		get_color_code(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void			put_pixel_to_image(t_img *img, int x, int y, uint32_t color);
void			fill_img(t_img *img, uint32_t color);

uint32_t		min(uint32_t a, uint32_t b);
uint32_t		max(uint32_t a, uint32_t b);


void			bresenham_quadrant1(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);
void			bresenham_quadrant2(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);
void			bresenham_quadrant3(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);
void			bresenham_quadrant4(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);
void			draw_line(const t_ivec2 *p1, const t_ivec2 *p2, t_img *img, uint32_t color);


float			is_in_polygon(int x, int y, const t_polygon *poly);
uint32_t		get_color_from_typewall(enum e_edge_type t);
void			swap(int *a, int *b);
uint8_t			same_edges(const t_ivec2 *a1, const t_ivec2 *a2, const t_ivec2 *b1, const t_ivec2 *b2);
t_ivec2			*get_near_point(t_data *data, t_ivec2 *new_point);
uint8_t			is_equ_ivec2(const t_ivec2 *p1, const t_ivec2 *p2);
uint8_t			is_point_in_polygon(const t_ivec2 *point, const t_polygon *polygon);
float			get_idist(const t_ivec2 *p1, const t_ivec2 *p2);
uint8_t			is_common_point(const t_ivec2 *a1, const t_ivec2 *a2, const t_ivec2 *b1, const t_ivec2 *b2);

void			draw_edge(t_data *data, t_ivec2 new_point);

uint32_t		nb_intersec_in_poly(const t_polygon *polygon, const t_ivec2 *new_point, const t_ivec2 *last_point);
float			first_intersect_dist_in_poly(const t_polygon *polygon, const t_ivec2 *new_point, const t_ivec2 *last_point);

uint8_t			check_segment(const t_data *data, const t_ivec2 *new_point, const t_ivec2 *last_point);
void			print_click(t_data *data, uint16_t id);

t_intersection	is_intersect(t_ivec2 a1, t_ivec2 a2, t_ivec2 b1, t_ivec2 b2);

void			print_points_list(const t_data *data);
void			print_edges_list(const t_data *data);

uint32_t		*parse_tga(char *name, t_tga_header *header);
uint32_t		invert_transparency(uint32_t c);

void			switch_select(t_data *data);
void			switch_drawing(t_data *data);
#endif
