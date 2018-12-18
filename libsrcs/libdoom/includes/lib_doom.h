#ifndef LIB_DOOM_H
# define LIB_DOOM_H

#include <libftmatrices.h>
#include <types.h>

typedef struct s_data t_data;

/*
** maths_tools.c
*/
t_vec3		calculate_normale_with_angles(float angle_x, float angle_y);
void		swap(int *a, int *b);
uint32_t	min(uint32_t a, uint32_t b);
uint32_t	max(uint32_t a, uint32_t b);
void		sclamp(int16_t *point, int16_t min, int16_t max);
void		clamp(int32_t *point, int32_t min, int32_t max);
void		fclamp(float *point, float min, float max);
int32_t		clamp_value(int32_t value, int32_t min, int32_t max);
float		norme(t_vec2 *v);
t_vec2		mult_vect_scalar(t_vec2 *v, float f);
void		normalize(t_vec2 *v);

/*
** mlx_tools.c
*/
int			close_hook(t_data *data);


#endif
