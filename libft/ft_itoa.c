/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 19:45:47 by alanteri          #+#    #+#             */
/*   Updated: 2014/11/16 20:03:13 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long		count(long nb, long i)
{
	long	count;

	count = nb;
	while (count / 10)
	{
		i++;
		count /= 10;
	}
	return (i);
}

char		*ft_itoa(int nb)
{
	char	*res;
	long	i;
	long	neg;
	long	tmp;

	neg = 0;
	i = 0;
	if (nb < 0)
	{
		tmp = (long)nb * -1;
		neg = 1;
		i += 1;
	}
	else
		tmp = (long)nb;
	res = (char *)malloc(sizeof(char) * count(nb, i) + 1);
	res[i + 1] = '\0';
	while (i--)
	{
		res[i] = tmp % 10 + 48;
		tmp /= 10;
	}
	if (neg == 1)
		res[0] = '-';
	return (res);
}
