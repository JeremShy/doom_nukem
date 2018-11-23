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
	char		*retour;
	int		nb;
	int		i;
	char		tab[17];

	if (nbr == 0)
		return (ft_strdup("0"));
	ft_strcpy(tab, "0123456789");
	nb = compte(nbr);
	retour = malloc(nb + 1);
	i = 1;
	while (nbr != 0)
	{
		retour[nb - i] = tab[nbr % 10];
		nbr /= 10;
		i++;
	}
	retour[nb] = '\0';
	return (retour);
}