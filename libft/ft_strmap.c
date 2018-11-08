/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 14:37:24 by alanteri          #+#    #+#             */
/*   Updated: 2014/11/15 16:52:29 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	size_t	size;
	char	*new;

	i = 0;
	if (s && f)
	{
		size = ft_strlen((char *)s);
		if (!(new = (char *)malloc(sizeof(char) * (size + 1))))
			return (NULL);
		while (i < size)
		{
			new[i] = f((char)s[i]);
			i++;
		}
		new[i] = '\0';
		return (new);
	}
	return (0);
}
