/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 12:04:49 by alanteri          #+#    #+#             */
/*   Updated: 2014/11/15 16:56:21 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*dest2;
	const char	*src2;
	char		tmp[n];

	i = 0;
	dest2 = (char *)dest;
	src2 = (const char *)src;
	while (i < n)
	{
		tmp[i] = src2[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		dest2[i] = tmp[i];
		i++;
	}
	return (dest);
}
