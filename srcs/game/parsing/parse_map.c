#include <game.h>
#include <file_format.h>

char		*open_file(const char *filename, off_t *file_size)
{
	struct stat	stat_buf;
	int			fd;
	char		*buf;

	if ((fd = open(filename, O_RDONLY)) == -1)
		ft_putendl_fd("Could not open file for reading.", 2);
	else if (fstat(fd, &stat_buf) == -1)
		ft_putendl_fd("Could not stat file", 2);
	else if (!(buf = malloc(stat_buf.st_size)))
		ft_putendl_fd("Memory error", 2);
	else if ((read(fd, buf, stat_buf.st_size)) == -1)
	{
		free(buf);
		ft_putendl_fd("Read error", 2);
	}
	else
	{
		*file_size = stat_buf.st_size;
		return (buf);
	}
	return (NULL);
}

struct s_fftexture		*parse_texture(t_data *data, struct s_fftexture *texture, int i)
{
	if (!(data->textures[i].addr = malloc(texture->size.x * texture->size.y * 4)))
		return (NULL);
	data->textures[i].w = texture->size.x;
	data->textures[i].h = texture->size.y;
	ft_memcpy(data->textures[i].addr, texture + 1, texture->size.x * texture->size.y * 4);
	return ((void*)texture + sizeof(struct s_fftexture) + (int)texture->size.x * (int)texture->size.y * 4);
}

uint8_t					parse_textures(t_data *data, struct s_fftexture *texture)
{
	int	i;

	i = 0;
	while (i < data->nb_textures)
	{
		if (!(texture = parse_texture(data, texture, i)))
			return (0);
		i++;
	}
	return (1);
}

uint8_t		parse_map(t_data *data, const char *filename)
{
	struct s_ffheader	*header;
	off_t				file_size;
	char				*buf;

	if (!(buf = open_file(filename, &file_size)))
		return (0);
	header = (struct s_ffheader*)(buf);
	if (!parse_header(data, header, file_size))
		free(buf);
	else if (!parse_points(data, (struct s_ivec2*)(buf + header->offset_points)))
		free(buf);
	else if (!parse_edges(data, (struct s_ffwall *)(buf + header->offset_walls)))
		free(buf);
	else if (!parse_sectors(data, (struct s_ffsector*)(buf + sizeof(struct s_ffheader)), buf))
		free(buf);
	else if (!parse_textures(data, (struct s_fftexture*)(buf + header->offset_texture)))
		free(buf);
	else
	{
		printf("offset_walls : %lld\n", header->offset_walls);
		free(buf);
		return (1);
	}
	return (0);
}
