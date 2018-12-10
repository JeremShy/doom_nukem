#include <editor.h>

uint8_t	load_textures(t_data *data, const char *extension, const char *folder)
{
	DIR				*dir;
	struct dirent	*entry;
	char			buf[514];

	if (!(dir = opendir(folder)))
	{
		ft_putendl_fd("Couldn't open dir", 2);
		return (0);
	}
	while ((entry = readdir(dir)))
	{
		printf("file : %.*s\n", entry->d_namlen, entry->d_name);
		if (entry->d_namlen >= 5 && ft_strcmp(entry->d_name + entry->d_namlen - 4, (char*)extension) == 0)
		{
			ft_strcpy(buf, (char*)folder);
			buf[ft_strlen(folder)] = '/';
			ft_strncpy(buf + ft_strlen(folder) + 1, entry->d_name, entry->d_namlen);
			buf[ft_strlen(folder) + 1 + entry->d_namlen] = '\0';
			printf("We have to load : %s\n", buf);
			create_image_from_png(data, IMG_START_TEXTURES + data->nbr_textures, buf, NULL);
			(data->nbr_textures)++;
		}
	}
	closedir(dir);
	return (1);
}
