#include <lib_doom.h>

int		close_hook(t_data *data)
{
	(void)data;
	exit(EXIT_SUCCESS);
}