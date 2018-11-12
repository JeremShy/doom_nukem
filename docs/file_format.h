# include <stdint.h>

/*
** Format de fichier des maps :
*/

typedef struct	s_vec2 {
	float	x;
	float	y;
}				t_vec2;

typedef struct	s_vec3 {
	float	x;
	float	y;
	float	z;
}				t_vec3;

struct			s_texture
{
};

struct	s_header {
	struct s_vec2	size;

	struct s_vec2	player_pos;

	uint16_t		sectors_number;
	uint16_t		walls_number;
	uint16_t		texture_number;
	uint16_t		sprites_number;

	uint32_t		offset_walls;
};

struct		s_wall {
			uint16_t	id;
			t_vec2		point;
			uint16_t	texture;
			uint16_t	next_sector;
};

struct	s_sector {
	uint16_t			id;
	uint16_t			walls_number;

	t_vec3				normale_sol;
	float				hauteur_sol;
	uint16_t			texture_sol;

	t_vec3				normale_plafond;
	float				hauteur_plafond;
	uint16_t			texture_plafond;

	uint16_t			texture_up;
	uint16_t			texture_down;

	float				ambient_light;
	uint32_t			next_sector;

	// uint16_t			walls[walls_number];
};


struct s_map {
	int64_t			magic_number;
	struct s_header	header;

	struct s_sector	*sectors;
/*
** Liste des secteurs entrecoupe des walls de chaque secteurs.
*/

	struct s_wall	*walls;
};
