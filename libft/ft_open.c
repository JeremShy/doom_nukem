/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 20:38:30 by alanteri          #+#    #+#             */
/*   Updated: 2017/12/04 17:49:39 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_open(char *file)
{
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_putendl_fd("Error open", 2);
		perror(file);
		exit(0);
	}
	return (fd);
}
