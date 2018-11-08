/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 13:49:37 by alanteri          #+#    #+#             */
/*   Updated: 2014/11/12 13:22:11 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *foin, const char *aiguille)
{
	int		i;
	int		j;

	i = 0;
	if (aiguille[i] == '\0')
		return ((char *)foin);
	while (foin[i])
	{
		j = 0;
		while (foin[i] == aiguille[j])
		{
			if (aiguille[j + 1] == '\0')
				return ((char *)&foin[i - j]);
			i++;
			if (foin[i] == aiguille[j])
				i--;
			j++;
		}
		i++;
	}
	return (NULL);
}
