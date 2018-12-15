#include <editor.h>
#include <file_format.h>

void		fill_sectors(t_data *data, uint8_t *addr, uint16_t *hash_map_edges, int16_t *hash_map_textures)
{
	struct s_sector	*current_sec;
	uint16_t		*current_wall;
	uint32_t		i;
	int				wall_i; // (LOL)

	i = 0;
	current_sec = (struct s_sector*)(addr + sizeof(struct s_header));
	while (i < data->max_element_id)
	{
		if (data->elements[i].enabled)
		{
			current_sec->id = i;
			current_sec->walls_number = data->elements[i].polygon.nb_points;
			calculate_normale_with_angles(current_sec->normal_floor, data->elements[i].angle_floor.x, data->elements[i].angle_floor.y);
			current_sec->height_floor = data->elements[i].height_floor;
			
			current_sec->texture_floor = hash_map_textures[data->elements[i].texture_floor];

			calculate_normale_with_angles(current_sec->normal_ceiling, data->elements[i].angle_ceiling.x, data->elements[i].angle_ceiling.y);
			current_sec->height_ceiling = data->elements[i].height_ceiling;
			current_sec->texture_ceiling = hash_map_textures[data->elements[i].texture_ceiling];

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

void	fill_walls(t_data *data, uint8_t *walls_addr, uint16_t *hash_map_edges, uint16_t *hash_map_points, int16_t *hash_map_textures)
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
			else if (data->edges[i].type == PORTAL)
			{
				current_wall->texture_up = hash_map_textures[data->edges[i].texture_up];
				current_wall->texture_down = hash_map_textures[data->edges[i].texture_down];
				find_next_sectors(data, current_wall, &data->edges[i]);
				printf("Wall[%d] : \n", i);
				printf("next_sector_1 : %d, next_sector_2 : %d\n", current_wall->next_sector_1, current_wall->next_sector_2);
			}
			else
			{
				printf("WTF 69\n");
			}
		}
		i++;
	}
}

void	fill_header(t_data *data, uint8_t *addr, int16_t *hash_map_textures)
{
	struct s_header	*header;

	header = (struct s_header*)addr;

	header->size = (t_ivec2){DRAWING_ZONE_WIDTH, DRAWING_ZONE_HEIGHT};
	header->player_pos = (t_vec2){DRAWING_ZONE_WIDTH / 2, DRAWING_ZONE_HEIGHT / 2}; // TODO
	header->sectors_number = calculate_nb_sectors(data);
	header->walls_number = calculate_nb_edges(data);
	header->texture_number = calculate_nb_textures(data, hash_map_textures);
	header->sprites_number = 0; // TODO
	header->objects_number = 0; // TODO

	header->offset_walls = sizeof(struct s_header) + calculate_size_sectors(data);
	header->offset_texture = header->offset_walls + calculate_nb_edges(data) * sizeof(struct s_wall);
	header->offset_audio = header->offset_texture + calculate_size_textures(data, hash_map_textures);
	header->offset_objects = header->offset_audio + calculate_size_audios(data);
}

void	fill_textures(t_data *data, uint8_t *addr, int16_t *hash_map_textures)
{
	uint16_t			i;
	uint16_t			current_in_file;
	struct s_texture	*t;

	i = IMG_START_TEXTURES;
	current_in_file = 0;
	t = (struct s_texture*)addr;
	while (i < data->nbr_textures + IMG_START_TEXTURES)
	{
		if (hash_map_textures[i] == current_in_file)
		{
			printf("Filling texture %d\n", current_in_file);
			t->id = current_in_file;
			t->size = (t_vec2){data->imgs[i].original_h, data->imgs[i].original_w};

			ft_memcpy((uint8_t*)t + sizeof(struct s_texture), data->imgs[i].original, data->imgs[i].original_h * data->imgs[i].original_w * 4);

			t = (struct s_texture*)((uint8_t*)t + sizeof(struct s_texture) + data->imgs[i].original_h * data->imgs[i].original_w * 4);
			current_in_file++;
			i = IMG_START_TEXTURES - 1;
		}
		i++;
	}
}

uint8_t		save_scene(t_data *data)
{
	int				fd;
	uint8_t			*addr;
	size_t			file_size;
	struct s_header	*header;
	uint16_t		*hash_map_edges;
	uint16_t		*hash_map_points;
	int16_t			*hash_map_textures;

	if (!(hash_map_edges = fill_hash_map_edges(data)))
		return (0);
	if (!(hash_map_points = fill_hash_map_points(data)))
	{
		free(hash_map_edges);
		return (0);
	}
	if (!(hash_map_textures = fill_hash_map_textures(data)))
	{
		free(hash_map_edges);
		free(hash_map_points);
		return (0);
	}
	if ((fd = open(data->scene_name, O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1)
	{
		ft_putendl_fd("Error : Couldn't open scene file for writing", 2);
		free(hash_map_edges);
		free(hash_map_points);
		free(hash_map_textures);
		return (0);
	}
	file_size = calculate_file_size(data, hash_map_textures);
	printf("file size : %zu\n", file_size);
	if (!(addr = malloc(file_size)))
	{
		ft_putendl_fd("Memory error", 2);
		free(hash_map_edges);
		free(hash_map_points);
		free(hash_map_textures);
		return (0);
	}
	ft_bzero(addr, file_size);

	header = (struct s_header*)addr;

	fill_header(data, addr, hash_map_textures);
	fill_sectors(data, addr, hash_map_edges, hash_map_textures);

	fill_walls(data, addr + header->offset_walls, hash_map_edges, hash_map_points, hash_map_textures);
	fill_textures(data, addr + header->offset_texture, hash_map_textures);

	write(fd, addr, file_size);
	exit (0);
}
