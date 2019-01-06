#include <game.h>

uint8_t						parse_header(t_data *data, struct s_ffheader *header, off_t file_size)
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



		data->player.pos.x = header->player_pos.x;
		data->player.pos.y = header->player_pos.y;
		data->player.pos.z = 0;

		data->nb_sectors = header->sectors_number;
		data->nb_points = header->points_number;
		data->nb_edges = header->walls_number;
		data->nb_textures = header->texture_number;

		printf("data->player.pos : {%f, %f]\n", data->player.pos.x, data->player.pos.y);
		printf("data->nb_sectors : %d\n", data->nb_sectors);
		printf("data->nb_points : %d\n", data->nb_points);
		printf("data->nb_edges : %d\n", data->nb_edges);
		printf("data->nb_imgs : %d\n", data->nb_textures);


		//TODO : sprites
		//TODO : objects

		return (1);
	}
	return (0);
}

uint8_t	parse_points(t_data *data, t_ivec2 *points)
{
	int	i;

	if (!(data->points = malloc(data->nb_points * sizeof(struct s_ivec2))))
		return (0);
	if (!(data->points_screen = malloc(data->nb_points * sizeof(struct s_ivec2))))
		return (0);
	if (!(data->used_points = malloc(data->nb_points * sizeof(uint8_t))))
		return (0);
	if (!(data->project_normal = malloc(data->nb_points * sizeof(float))))
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

uint8_t	parse_edges(t_data *data, struct s_ffwall *file_wall)
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
