#ifndef GAME_H
# define GAME_H

# include <doom_nukem.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <file_format.h>
# include <sys/time.h>

# define WIN_SIZE_X 1600
# define WIN_SIZE_Y 900 // /!\ Can't modify

# define MAX_SECTOR_NBR 256
# define MAX_SECTOR_EDGES 64

# define MAX_TEXTURES 255

# define MAX_POINTS_NBR MAX_SECTOR_NBR * MAX_SECTOR_EDGES

# define FOV (M_PI / 2)
# define HALF_FOV (M_PI / 4)

# define SPEED 50

typedef struct s_sector t_sector;

enum					e_edge_type
{
						WALL,
						PORTAL
};

typedef struct			s_img
{
	void				*ptr;
	int					w;
	int					h;
	uint32_t			*addr;
}						t_img;

typedef struct			s_texture
{
	int					w;
	int					h;
	uint32_t			*addr;
}						t_texture;

typedef struct			s_edge
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
}						t_edge;

typedef struct			s_sector
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

}						t_sector;

typedef struct			s_player
{
	t_vec3	pos;
	t_vec3	dir;
}						t_player;

typedef struct			s_bunch
{
	uint16_t	id_sector;

	uint16_t	id_begin;
	uint16_t	id_end;
}						t_bunch;

typedef struct			s_data
{
	int					deltatime;
	int					lasttime;

	uint8_t				need_update;

	uint8_t				key[MAX_KEY + 1];

	t_mlx				mlx;
	t_img				screen;

	t_texture			textures[MAX_TEXTURES];
	uint16_t			nb_textures;

	t_vec2				size;
	
	t_player			player;

	uint32_t			nb_sectors;
	t_sector			*sectors;

	int32_t				nb_edges;
	t_edge				*edges;

	int32_t				nb_points;
	t_vec2				*points;

	uint8_t				*used_points;
	float				*project_normal;

	int32_t				nb_points_screen;
	t_vec2				*points_screen;

	float				*angle_dir_point;

	uint8_t				*visible_edges;

	t_mat4x4			mat_rot_dir_left;
	t_mat4x4			mat_rot_dir_right;
	t_mat4x4			look_at;
	t_mat4x4			projection;

	int32_t				nb_bunches;
	t_bunch				bunches[MAX_SECTOR_NBR * MAX_SECTOR_EDGES / 2];
	t_bunch				sorted_bunches[MAX_SECTOR_NBR * MAX_SECTOR_EDGES / 2];
}						t_data;

/*
** : visible_edges :
** : bit 0 -> visible 
** : bit 1 -> deja utilisé
**
** : bit 2 - 7 : réservé
*/


/*
** parsing/parse_input.c
*/
uint8_t					parse_map(t_data *data, const char *filename);

/*
** parsing/sector.c
*/
uint8_t					parse_sectors(t_data *data, struct s_ffsector *file_sector);

/*
** parsing/simple_map.c
*/
uint8_t					parse_points(t_data *data, t_ivec2 *points);
uint8_t					parse_edges(t_data *data, struct s_ffwall *file_wall);
uint8_t					parse_header(t_data *data, struct s_ffheader *header, off_t file_size);

/*
** bresenham.c
*/
void					draw_line(const t_ivec2 *p1, const t_ivec2 *p2, t_img *img, uint32_t color);

/*
** bresenham_quadrants.c
*/
void					bresenham_quadrant1(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);
void					bresenham_quadrant2(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);
void					bresenham_quadrant3(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);
void					bresenham_quadrant4(t_ivec2 p1, t_ivec2 p2, t_img *img, uint32_t color);

/*
** flood_bunches.c
*/
void					flood_bunches(t_data *data);

/*
** handle_key_events.c
*/
void					handle_key_events(t_data *data);

/*
** key_hook.c
*/
int						key_release(int keycode, t_data *data);
int						key_press(int keycode, t_data *data);

/*
** log.c
*/
void					init_log(const char *logfile);
void					do_log(const char *str, ...);

/*
** mlx_loop.c
*/
int						loop(t_data *data);

/*
** mlx_img_func.c
*/
uint32_t				get_color_code(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void					put_pixel_to_image(t_img *img, int x, int y, uint32_t color);
void					fill_img(t_img *img, uint32_t color);

/*
** mouse_hook.c
*/
int						mouse_hook(int button, int x, int y, t_data *data);

/*
** points_angle.c
*/
float				get_angle_player_point(t_player *player, t_vec2 *point);
void					fill_hash_pt_fov(t_data *data);

/*
** projection_point.c
*/
uint8_t		project_points_on_normal(t_data *data);

#endif
