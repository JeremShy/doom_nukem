#ifndef EDITOR_H
# define EDITOR_H

# include <background_editor.h>
# include <doom_nukem.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <ft_printf.h>
# include <dirent.h>

# define WIN_SIZE_X 1600
# define WIN_SIZE_Y 1050 // /!\ Can't modify

# define DRAWING_ZONE_WIDTH 1061
# define DRAWING_ZONE_HEIGHT 900

# define IMG_BACKGROUND 0
# define IMG_DRAWING 1
# define SQUARE_POINT 2
# define IMG_START_TEXTURES 3

# define MAX_TEXTURES 255

# define MAX_IMAGE (SQUARE_POINT + MAX_TEXTURES + 1)

# define MAX_ELEMENT_NBR 1024
# define MAX_POLYGON_EDGES 64

# define GRID_ROUND 25

# define MAP_SIZE 100 // The saved map size

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
	SELECTING,
	DELETE_SECTOR,
	MOVE_POINT
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
	t_ivec2				*p1;
	t_ivec2				*p2;

	uint16_t			texture_up;
	uint16_t			texture_down;
	uint16_t			texture_wall;
}				t_edge;

typedef struct		s_polygon
{
	uint8_t			nb_points;
	int8_t			finished;

	t_edge			*edges[MAX_POLYGON_EDGES];
}					t_polygon;

typedef struct			s_element
{
	uint16_t			id;

	enum e_elem_type	type;

	uint8_t				printable;

	uint8_t				clickable;
	uint8_t				enabled;
	t_on_click_func		on_click_func;

	uint16_t			texture_floor;
	t_ivec2				angle_floor;
	int16_t				height_floor;

	uint16_t			texture_ceiling;
	t_ivec2				angle_ceiling;
	int16_t				height_ceiling;

	uint32_t			light;

	t_polygon			polygon;
}						t_element;

typedef struct	s_input
{
	uint16_t			texture_wall;
	enum e_edge_type	wall_type;

	int32_t				id_current_element;
	int32_t				id_current_point;

	t_edge				*current_edge;

	enum e_input_mode	mode;

	uint8_t				button[8];
	uint8_t				key[300];

	uint16_t			texture_floor;
	t_ivec2				angle_floor;
	int16_t				height_floor;

	uint16_t			texture_ceiling;
	t_ivec2				angle_ceiling;
	int16_t				height_ceiling;

	uint16_t			texture_up;
	uint16_t			texture_down;
	uint32_t			light;
}				t_input;

typedef struct	s_data
{
	t_mlx		mlx;
	const char	*scene_name;

	t_img		imgs[MAX_IMAGE];

	uint8_t		update_drawing;
	t_input		input;

	uint32_t	nb_elements;
	t_element	elements[MAX_ELEMENT_NBR];

	t_edge		edges[MAX_POINTS_NBR];
	int32_t		max_edge_id;

	t_ivec2		points[MAX_POINTS_NBR];
	int32_t		max_point_id;

	uint8_t		used_point[MAX_POINTS_NBR];

	uint16_t	nbr_textures;
}				t_data;

/*
** binary_tools.c
*/
uint32_t		get_conv_32(const uint32_t *nbr);
uint64_t		get_conv_64(const uint64_t *nbr);
uint8_t			reverse_byte_ptr(const uint8_t *input);
uint8_t			reverse_byte(const uint8_t input);
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
** calculate_nbs.c
*/

size_t			calculate_size_audios(t_data *data);
size_t			calculate_size_textures(t_data *data);
size_t			calculate_size_sectors(t_data *data);
size_t			calculate_file_size(t_data *data);

/*
** calculate_nbs.c
*/
size_t			calculate_nb_edges(t_data *data);
size_t			calculate_nb_sectors(t_data *data);

/*
** create_edge.c
*/
void			create_edge(t_data *data, t_ivec2 new_point);

/*
** debug.c
*/
void			liste_edges(t_data *data);
void			liste_points(t_data *data);

/*
** delete.c
*/
void			delete_point(t_ivec2 *point, t_data *data);
void			delete_edge(t_edge *edge, t_data *data);
void			delete_element(t_element *elem, t_data *data);

/*
** edge_tools.c
*/
t_edge			*get_nearest_edge_except(const t_ivec2 *point, t_data *data, float *min, t_ivec2 *exept);
t_edge			*get_nearest_edge(const t_ivec2 *point, t_data *data, float *min);

/*
** editor_interactions.c
*/
void			wall_texture(uint8_t side, t_data *data);
void			up_texture(uint8_t side, t_data *data);
void			down_texture(uint8_t side, t_data *data);
void			floor_texture(uint8_t side, t_data *data);
void			ceiling_texture(uint8_t side, t_data *data);
void			ceil_angle_y(uint8_t side, t_data *data);
void			ceil_angle_x(uint8_t side, t_data *data);
void			ceil_height(uint8_t side, t_data *data);
void			floor_angle_y(uint8_t side, t_data *data);
void			floor_angle_x(uint8_t side, t_data *data);
void			floor_height(uint8_t side, t_data *data);
void			light(uint8_t side, t_data *data);

/*
** file_listing.c
*/
uint8_t			load_textures(t_data *data, const char *extension, const char *folder);

/*
** imaths.c
*/
t_ivec2			vec_from_points(const t_ivec2 *p1, const t_ivec2 *p2);
float			idist(const t_ivec2 *p1, const t_ivec2 *p2);
float			inorm(const t_ivec2 *v1);
int				idot_prod(const t_ivec2 *v1, const t_ivec2 *v2);
float			iangle(const t_ivec2 v1, const t_ivec2 v2);

/*
** intersect_two_segments.c
*/
t_intersection	intersect_two_segments(t_ivec2 a1, t_ivec2 a2, t_ivec2 b1, t_ivec2 b2);

/*
** intersection.c
*/
uint32_t		nb_intersec_in_poly(const t_polygon *polygon, const t_ivec2 *new_point, const t_ivec2 *last_point);
float			is_in_polygon(const t_ivec2 *point, const t_polygon *poly);
uint8_t			is_point_in_polygon(const t_ivec2 *point, const t_polygon *polygon);

/*
** key_hook.c
*/
void			draw_polygon(t_polygon *polygon, t_data *data);
void			switch_select(t_data *data);
void			switch_drawing(t_data *data);
int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
void			switch_delete_sector(t_data *data);
void			switch_move_point(t_data *data);
void			switch_wall_type(t_data *data);

/*
** loop_hook.c
*/
int				loop_hook(t_data *data);

/*
** main.c
*/
uint8_t			create_image(t_data *data, int id, int w, int h);

/*
** maths_tools.c
*/
void			swap(int *a, int *b);
uint32_t		min(uint32_t a, uint32_t b);
uint32_t		max(uint32_t a, uint32_t b);
void			clamp(int32_t *point, int32_t min, int32_t max);
void			fclamp(float *point, float min, float max);
int32_t			clamp_value(int32_t value, int32_t min, int32_t max);
void			sclamp(int16_t *point, int16_t min, int16_t max);

/*
** mlx_img_func.c
*/
uint32_t		get_color_code(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void			put_pixel_to_image(t_img *img, int x, int y, uint32_t color);
void			fill_img(t_img *img, uint32_t color);

/*
** mlx_hook.c
*/
t_element		*get_polygon_from_point(t_data *data, t_ivec2 *point);
int				mouse_motion(int x, int y, t_data *data);
int				mouse_press(int button, int x, int y, t_data *data);
int				mouse_release(int button, int x, int y, t_data *data);
int				drawing_zone(int x, int y, t_data *data);

/*
** parser_png.c
*/
uint8_t			create_image_from_png(t_data *data, int id_img, const char *name, t_ivec2 *size);

/*
** parser_tga.c
*/
uint32_t		*parse_tga(const char *name, t_tga_header *header);
uint32_t		invert_transparency(uint32_t c);
uint8_t			create_image_from_tga(t_data *data, int id_img, const char *name, t_ivec2 *size);

/*
** polygon.c
*/
void			print_click(t_data *data, uint16_t id);
uint8_t			check_point(t_data *data, const t_ivec2 *point, t_ivec2 *exept);
uint8_t			check_segment(t_data *data, const t_ivec2 *new_point, const t_ivec2 *last_point);

/*
** save_scene.c
*/
uint8_t			save_scene(t_data *data);

/*
** tools.c
*/
uint32_t		get_color_from_typewall(enum e_edge_type t);
uint8_t			same_edges(const t_ivec2 *a1, const t_ivec2 *a2, const t_ivec2 *b1, const t_ivec2 *b2);
t_ivec2			get_grid_point(t_ivec2 point);
uint32_t		get_nearest_point(t_data *data, t_ivec2 *point, int32_t *id);
uint8_t			is_equ_ivec2(const t_ivec2 *p1, const t_ivec2 *p2);
uint32_t		get_idpoint_from_addr(const t_ivec2 *point, t_data *data);

// t_data			data;

#endif
