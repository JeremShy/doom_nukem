/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 13:40:32 by alanteri          #+#    #+#             */
/*   Updated: 2014/11/15 16:08:16 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	size_t	i;
	size_t	size;

	if (s && f)
	{
		i = 0;
		size = ft_strlen(s);
		while (i < size)
		{
			f(&s[i]);
			i++;
		}
	}
}
