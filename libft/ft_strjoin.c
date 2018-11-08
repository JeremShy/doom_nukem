/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 14:38:48 by alanteri          #+#    #+#             */
/*   Updated: 2014/11/12 15:31:09 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*new;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = (ft_strlen(s1) + ft_strlen(s2) + 1);
	new = (char *)malloc(sizeof(char) * (size));
	if (new == NULL)
		return (NULL);
	ft_bzero(new, size);
	ft_strcat(new, (char *)s1);
	ft_strcat(new, (char *)s2);
	return (new);
}
