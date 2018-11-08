/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 15:45:42 by alanteri          #+#    #+#             */
/*   Updated: 2014/11/15 16:41:03 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	size;
	char	*new;

	i = 0;
	if (s && f)
	{
		size = ft_strlen((char *)s);
		if (!(new = (char *)malloc(sizeof(char) * size + 1)))
			return (NULL);
		while (i < size)
		{
			new[i] = f(i, s[i]);
			i++;
		}
		new[i] = '\0';
		return (new);
	}
	return (0);
}
