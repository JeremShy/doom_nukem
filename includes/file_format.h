#ifndef FILE_FORMAT_H
# define FILE_FORMAT_H

# include <stdint.h>
# include <types.h>
# include <libftmatrices.h>

# define DOOM_MAGIC 0x4d4f4f44474d434a

/*
** Format de fichier des maps :
** v0.2
*/

typedef struct s_data	t_data;

struct			s_fftexture
{
	uint16_t	id;
		t_vec2		size;
//	uint32_t		data[size.x * size.y]; // r,g,b,a
};

struct			s_ffaudio
{
	uint16_t	id;
	uint32_t	size;
};
					
struct	s_ffheader {
	uint64_t		magic;
	uint32_t		file_size;

	struct s_ivec2	size;
	struct s_vec2	player_pos;

	uint16_t		sectors_number;
	uint16_t		points_number;
	uint16_t		walls_number;
	uint16_t		texture_number;

	uint16_t		sprites_number;
	uint16_t		objects_number;
	uint64_t		offset_points;
	uint64_t		offset_walls;
	uint64_t		offset_texture;
	uint64_t		offset_audio;
	uint64_t		offset_objects;
};

struct		s_ffwall {
	uint16_t	id;
	
	uint16_t	p1;
	uint16_t	p2;

	uint16_t	texture;

	uint16_t	texture_up;
	uint16_t	texture_down;

	uint16_t	next_sector_1; // -1 if a portal
	uint16_t	next_sector_2; // -1 if a portal
};

struct	s_ffsector {
	uint16_t			id;
	uint16_t			walls_number;

	t_vec3				normal_floor;
	float				height_floor;
	uint16_t			texture_floor;

	t_vec3				normal_ceiling;
	float				height_ceiling;
	uint16_t			texture_ceiling;

	float				ambient_light;

	// uint16_t			walls[walls_number];
};

struct	s_ffobject {
	uint16_t	id;

	uint16_t	id_object;
	t_vec2		position;
	// paramaeter ?
};

/*
struct s_map {
	struct s_header	header;

	struct s_sector		sectors[]; Liste des secteurs entrecoupe des walls de chaque secteurs.
	struct s_ivec2		points[];
	struct s_wall		walls[]; Donnees des murs
	struct s_texture	texture[];
	struct s_audio		audio[];
	struct s_object		objects[];
};
*/

#endif
