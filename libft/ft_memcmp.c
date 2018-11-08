/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 15:17:35 by alanteri          #+#    #+#             */
/*   Updated: 2014/11/15 16:57:40 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*s3;
	const char	*s4;

	i = 0;
	s3 = s1;
	s4 = s2;
	while (i < n)
	{
		if ((unsigned char)s3[i] != (unsigned char)s4[i])
			return ((unsigned char)s3[i] - (unsigned char)s4[i]);
		i++;
	}
	return (0);
}
