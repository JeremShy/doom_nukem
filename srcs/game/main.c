#include <game.h>

static uint8_t	create_image(t_mlx *mlx, t_img *img, int w, int h)
{
	int	bpp;
	int	endian;
	int	size_line;

	if (!(img->ptr = mlx_new_image(mlx->mlx_ptr, w, h)))
		ft_putendl_fd("Error: Couldn't create new image.", 2);
	else if (!(img->addr = (void*)mlx_get_data_addr(img->ptr, &bpp, &size_line, &endian)))
		ft_putendl_fd("Error : Couldn't get data_addr of the new image.", 2);
	else if (bpp != 32 || endian != 0 || size_line != w * 4)
		ft_putendl_fd("Error : Unexpected bpp and endian.", 2);
	else
	{
		img->h = h;
		img->w = w;
		return (1);
	}
	return (0);
}

static uint8_t	ft_init(t_mlx *mlx, t_img *img, uint16_t size_x, uint16_t size_y)
{
	if (!(mlx->mlx_ptr = mlx_init()))
		ft_putendl_fd("Error: Can't init mlx->", 2);
	else if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, size_x, size_y, "Doom Nukem : Map editor")))
		ft_putendl_fd("Error: Can't init window.", 2);
	else if (!create_image(mlx, img, 1600, 900))
		return (0);
	else
		return (1);
	return (0);
}

void	put_pixel_to_image(t_img *img, int x, int y, uint32_t color)
{
	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
	{
		dprintf(2, "Error 12. (put_pixel_to_image)\n");
		dprintf(2, "{img, x, y, color : {%p, %d, %d, %#X}\n", img, x, y, color);
		exit(EXIT_FAILURE);
	}
	img->addr[x + y * img->w] = color;
}

void	fill_img(t_img *img, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->w)
	{
		j = 0;
		while (j < img->h)
		{
			put_pixel_to_image(img, i, j, color);
			j++;
		}
		i++;
	}
}

uint32_t	get_color_code(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (((int)b << 0) | ((int)g << 8) | ((int)r << 16) | ((int)a << 24));
}

uint32_t	invert_transparency(uint32_t c)
{
	int	alpha;

	alpha = c >> 24;
	alpha = 255 - (uint8_t)alpha;
	return (alpha << 24 | (c & 0x00ffffff));
}

uint32_t	*parse_tga(char *name, t_tga_header *header)
{
	uint32_t	*img_data;
	int			fd;
	struct stat	buf;

	if ((fd = open(name, O_RDONLY)) == -1)
	{
		dprintf(2, "Error : Couldn't open file %s\n", name);
		return (NULL);
	}
	if ((fstat(fd, &buf)) == -1)
	{
		dprintf(2, "Error : Couldn't open file %s\n", name);
		return (NULL);
	}
	void *addr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE | MAP_FILE, fd, 0);
	if (addr == NULL)
	{
		printf("map error\n");
		return (NULL);
	}
	print_memory(addr, 16);

	*header = *(t_tga_header *)addr;
	printf("id_length : %hhu\n", header->id_length);
	printf("color_map_type : %hhu\n", header->color_map_type);
	printf("image_type : %hhu\n", header->image_type);
	if (header->id_length != 0 || header->color_map_type != 0 || header->image_type != 2
		|| ft_memcmp(header->color_map_spec, "\0\0\0\0\0", 5) != 0)
	{
		dprintf(2, "Error : tga file not handled.\n");
		return (NULL);
	}
	printf("image specs :\n");
	printf("x_origin : %hu\n", header->image_spec.x_origin);
	printf("y_origin : %hu\n", header->image_spec.y_origin);
	printf("width : %hu\n", header->image_spec.width);
	printf("height : %hu\n", header->image_spec.height);
	printf("pixel_depth : %hhu\n", header->image_spec.pixel_depth);
	printf("descriptor : %hhu\n", header->image_spec.descriptor);
	img_data = addr + sizeof(t_tga_header);
	return (img_data);
}

int main(int ac, char **av)
{
	t_mlx			mlx;
	t_img			img;
	t_img			white_img;
	t_tga_header	header;
	uint32_t		*img_data;
	
	if (ac != 2)
	{
		printf("Error\n");
		return (1);
	}

	if (!(img_data = parse_tga(av[1], &header)))
		return (1);
	if (!ft_init(&mlx, &img, header.image_spec.width, header.image_spec.height))
	{
		printf("mlx error.\n");
	}

	create_image(&mlx, &white_img, header.image_spec.width, header.image_spec.height);
	fill_img(&white_img, get_color_code(255, 255, 255, 0));


	int	i = 0;
	while (i < header.image_spec.width * header.image_spec.height)
	{
		put_pixel_to_image(&img, i % header.image_spec.width, header.image_spec.height - i / header.image_spec.width, invert_transparency(img_data[i]));
		i++;
	}

	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, white_img.ptr, 0, 0);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, img.ptr, 0, 0);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
