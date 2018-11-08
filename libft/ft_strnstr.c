/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 12:35:22 by alanteri          #+#    #+#             */
/*   Updated: 2014/11/16 20:34:50 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *foin, const char *aiguille, size_t n)
{
	size_t		i;
	size_t		j;

	i = 0;
	if (aiguille[i] == '\0')
		return ((char *)foin);
	while (foin[i])
	{
		j = 0;
		while (foin[i] == aiguille[j] && (i < n) && foin[i] != '\0')
		{
			if (aiguille[j + 1] == '\0')
				return ((char *)&foin[i - j]);
			i++;
			if (foin[i] == aiguille[j])
				i--;
			j++;
		}
		if (foin[i] != '\0')
			i++;
	}
	return (NULL);
}
