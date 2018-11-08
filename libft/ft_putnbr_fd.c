/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 17:51:11 by alanteri          #+#    #+#             */
/*   Updated: 2014/11/16 20:23:17 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	min;
	char			c;

	min = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		min = -min;
	}
	if (min > 9)
		ft_putnbr_fd((min / 10), fd);
	c = (char)(48 + min % 10);
	write(fd, &c, 1);
}
