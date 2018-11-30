#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <stdio.h>
# include <libft.h>
# include <stdlib.h>
# include <mlx.h>
# include <stdint.h>
# include <math.h>

# define KEY_ESCAPE 53
# define KEY_BACKQUOTE 50
# define KEY_S 1
# define KEY_D 2
# define KEY_E 14
# define KEY_P 35
# define KEY_X 7
# define KEY_L 37
# define KEY_M 46
# define KEY_E 14

typedef struct	s_vec2 {
	float	x;
	float	y;
}				t_vec2;

typedef struct	s_ivec2 {
	int	x;
	int	y;
}				t_ivec2;

typedef struct	s_vec3 {
	float	x;
	float	y;
	float	z;
}				t_vec3;

#endif
