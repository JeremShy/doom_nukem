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
