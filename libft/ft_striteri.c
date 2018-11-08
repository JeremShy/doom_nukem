/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 14:22:09 by alanteri          #+#    #+#             */
/*   Updated: 2014/11/15 16:09:08 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;
	int	size;

	if (s && f)
	{
		i = 0;
		size = ft_strlen(s);
		while (i < size)
		{
			f(i, &s[i]);
			i++;
		}
	}
}
