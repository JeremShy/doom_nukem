/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 14:34:31 by alanteri          #+#    #+#             */
/*   Updated: 2014/11/16 20:20:34 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int	min;
	char			c;

	min = n;
	if (n < 0)
	{
		write(1, "-", 1);
		min = -min;
	}
	if (min > 9)
		ft_putnbr(min / 10);
	c = (char)(48 + min % 10);
	write(1, &c, 1);
}
