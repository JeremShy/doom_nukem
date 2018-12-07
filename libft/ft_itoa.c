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

#include <libft.h>

static int      compte(int nbr)
{
	int ret;

	ret = 0;
	while (nbr != 0)
	{
		nbr /= 10;
		ret++;
	}
	return (ret);
}

char            *ft_itoa(int nbr)
{
	char	*retour;
	int		nb;
	int		i;
	uint8_t	signe;

	signe = 0;
	if (nbr == 0)
		return (ft_strdup("0"));
	if (nbr < 0)
	{
		if (nbr == (int)0x80000000)
			return (ft_strdup("-2147483648"));
		retour = malloc(16);
		nbr *= -1;
		signe = 1;
		retour[0] = '-';
	}
	else
		retour = malloc(16);
	nb = compte(nbr);
	i = 1;
	while (nbr != 0)
	{
		retour[nb - i + signe] = '0' + (nbr % 10);
		nbr /= 10;
		i++;
	}
	retour[nb + signe] = '\0';
	return (retour);
}