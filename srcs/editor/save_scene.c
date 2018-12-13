#include <editor.h>
#include <file_format.h>

void		fill_sectors(t_data *data, uint8_t *addr, uint16_t *hash_map_edges)
{
	struct s_sector	*current_sec;
	uint16_t		*current_wall;
	uint32_t		i;
	int				wall_i; // (LOL)

	i = 0;
	current_sec = (struct s_sector*)(addr + sizeof(struct s_header));
	while (i < data->nb_elements)
	{
		if (data->elements[i].enabled)
		{
			current_sec->id = i;
			current_sec->walls_number = data->elements[i].polygon.nb_points;
			// current_sec->normal_floor = calculate normale floor
			current_sec->height_floor = data->elements[i].height_floor;
			current_sec->texture_floor = data->elements[i].texture_floor;

			// current_sec->normal_ceiling = calculate normale ceiling
			current_sec->height_ceiling = data->elements[i].height_ceiling;
			current_sec->texture_ceiling = data->elements[i].texture_ceiling;

			current_sec->ambient_light = data->elements[i].light;

			current_wall = (void*)current_sec + sizeof(struct s_sector);
			wall_i = 0;
			while (wall_i < data->elements[i].polygon.nb_points)
			{
				*current_wall = hash_map_edges[data->elements[i].polygon.edges[wall_i] - data->edges];
				printf("writing : %u in the file.\n", *current_wall);
				current_wall++;
				wall_i++;
			}
			current_sec++;
		}
		i++;
	}
}

void	fill_walls(t_data *data, uint8_t *walls_addr, uint16_t *hash_map_edges, uint16_t *hash_map_points)
{
	struct s_wall	*current_wall;
	uint16_t		i;

	current_wall = (struct s_wall*)walls_addr;
	i = 0;
	while (i < data->max_edge_id)
	{
		if (data->edges[i].used)
		{
			current_wall->id = hash_map_edges[i];
			current_wall->p1 = hash_map_points[data->edges[i].p1 - data->points];
			current_wall->p2 = hash_map_points[data->edges[i].p2 - data->points];
			if (data->edges[i].type == SOLID)
			{
				current_wall->texture = data->edges[i].texture_wall;
			}
			else
			{
				current_wall->texture_up = data->edges[i].texture_up;
				current_wall->texture_down = data->edges[i].texture_down;
			}
		}
		i++;
	}
}

void	fill_header(t_data *data, uint8_t *addr)
{
	struct s_header	*header;

	header = (struct s_header*)addr;

	header->size = (t_ivec2){MAP_SIZE, MAP_SIZE};
	// header->player pos
	header->sectors_number = calculate_nb_sectors(data);
	header->walls_number = calculate_nb_edges(data);
	header->texture_number = data->nbr_textures;
	// header->sprites_number;
	// header->objects_number;

	header->offset_walls = sizeof(struct s_header) + calculate_size_sectors(data);
	header->offset_texture = header->offset_walls + calculate_nb_edges(data) * sizeof(struct s_wall);
	header->offset_audio = header->offset_texture + calculate_size_textures(data);
	header->offset_objects = header->offset_audio + calculate_size_audios(data);
}

uint8_t		save_scene(t_data *data)
{
	int				fd;
	uint8_t			*addr;
	size_t			file_size;
	struct s_header	*header;
	uint16_t		*hash_map_edges;
	uint16_t		*hash_map_points;

	if (!(hash_map_edges = fill_hash_map_edges(data)))
		return (0);
	if (!(hash_map_points = fill_hash_map_points(data)))
	{
		free(hash_map_edges);
		return (0);
	}
	if ((fd = open(data->scene_name, O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1)
	{
		ft_putendl_fd("Error : Couldn't open scene file for writing", 2);
		return (0);
	}
	file_size = calculate_file_size(data);
	printf("file size : %zu\n", file_size);
	if (!(addr = malloc(file_size)))
	{
		ft_putendl_fd("Memory error", 2);
		return (0);
	}
	ft_bzero(addr, file_size);

	header = (struct s_header*)addr;

	fill_header(data, addr);
	fill_sectors(data, addr, hash_map_edges);

	addr = addr + header->offset_walls;
	fill_walls(data, addr, hash_map_edges, hash_map_points);


	write(fd, addr, file_size);
	exit (0);
}
