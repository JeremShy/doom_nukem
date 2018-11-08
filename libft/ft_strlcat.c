/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 17:42:36 by alanteri          #+#    #+#             */
/*   Updated: 2014/11/14 18:44:07 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!count)
		return (ft_strlen(src));
	if (!dest)
		return (0);
	while (dest[i] && i < count)
		i++;
	while (i + j < count - 1 && src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i + j != count)
		dest[i + j] = '\0';
	while (src[j])
		j++;
	return (i + j);
}
