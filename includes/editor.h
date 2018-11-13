#ifndef EDITOR_H
# define EDITOR_H

# include <doom_nukem.h>

# define WIN_SIZE_X 1600
# define WIN_SIZE_Y 900 // /!\ Can't modify

# define MAX_RECTANGLE_NBR 4096

struct			s_data;
struct			s_rectangle;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlx;

typedef void (*on_click_func)(struct s_data *data, int id);

typedef struct	s_rectangle
{
	uint8_t	enabled;
	uint32_t	id;
	t_vec2	bottom_left;
	t_vec2	up_right;
	on_click_func	func;
}				t_rectangle;

typedef struct	s_data
{
	t_mlx		mlx;

	int			nb_params;
	t_rectangle	params[MAX_RECTANGLE_NBR];
}				t_data;



int	loop_hook(t_data *data);
int	mouse_hook(int button, int x,int y, t_data *data);

void	rectangle_on_click(t_data *data, int id);
int8_t	in_rectangle(int x, int y, t_rectangle rect);


#endif
