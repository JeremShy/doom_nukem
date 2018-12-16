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

uint8_t		parse_header(t_data *data, struct s_ffheader *header, off_t file_size)
{
	if (file_size < (off_t)sizeof(struct s_ffheader))
		ft_putendl_fd("Size error", 2);
	else if (header->magic != DOOM_MAGIC)
		ft_putendl_fd("Invalid file format.", 2);
	else if (header->file_size != file_size)
		ft_putendl_fd("Invalid file size", 2);
	else
	{
		data->size.x = (float)header->size.x;
		data->size.y = (float)header->size.y;
		data->player.pos = header->player_pos;

		data->nb_sectors = header->sectors_number;
		data->nb_points = header->points_number;
		data->nb_edges = header->walls_number;
		data->nb_imgs = header->texture_number;

		printf("data->nb_sectors : %d\n", data->nb_sectors);
		printf("data->nb_points : %d\n", data->nb_points);
		printf("data->nb_edges : %d\n", data->nb_edges);
		printf("data->nb_imgs : %d\n", data->nb_imgs);


		//TODO : sprites
		//TODO : objects

		return (1);
	}
	return (0);
}

uint8_t		parse_points(t_data *data, t_ivec2 *points)
{
	int	i;

	if (!(data->points = malloc(data->nb_points * sizeof(struct s_ivec2))))
		return (0);
	i = 0;
	while (i < data->nb_points)
	{
		data->points[i].x = (float)points->x;
		data->points[i].y = (float)points->y;
		points++;
		i++;
	}
	return (1);
}

uint8_t		parse_edges(t_data *data, struct s_ffwall *file_wall)
{
	uint16_t		i;

	i = 0;
	if (!(data->edges = malloc(data->nb_edges * sizeof(struct s_edge))))
		return (0);
	while (i < data->nb_edges)
	{
		data->edges[i].id = i;
		data->edges[i].p1 = &(data->points[file_wall->p1]);
		data->edges[i].p2 = &(data->points[file_wall->p2]);

		if (file_wall->next_sector_1 == (uint16_t)-1u ||
			file_wall->next_sector_2 == (uint16_t)-1u)
		{
			data->edges[i].type = WALL;
			data->edges[i].texture_wall = file_wall->texture;
		}
		else
		{
			data->edges[i].next_sector_1 = &data->sectors[file_wall->next_sector_1];
			data->edges[i].next_sector_2 = &data->sectors[file_wall->next_sector_2];
			data->edges[i].type = PORTAL;
			data->edges[i].texture_up = file_wall->texture_up;
			data->edges[i].texture_down = file_wall->texture_down;
		}

		file_wall++;
		i++;
	}
	return (1);
}

struct s_ffsector		*parse_sector(t_data *data, struct s_ffsector *file_sector, uint16_t i)
{
	int	wall;

	data->sectors[i].id = i;

	data->sectors[i].texture_floor = file_sector->texture_floor;
	data->sectors[i].height_floor = file_sector->height_floor;
	data->sectors[i].normale_floor = file_sector->normal_floor;

	data->sectors[i].height_floor = file_sector->height_floor;

	return (file_sector);
}

uint8_t		parse_sectors(t_data *data, struct s_ffsector *file_sector)
{
	int	i;

	if (!(data->sectors = malloc(data->nb_sectors * sizeof(struct s_sector))))
		return (0);
	i = 0;
	while (i < data->nb_sectors)
	{
		file_sector = parse_sector(data, file_sector, i);
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
	else
	{
		printf("offset_walls : %lld\n", header->offset_walls);
		free(buf);
		return (1);
	}
	return (0);
}
