/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 19:45:47 by alanteri          #+#    #+#             */
/*   Updated: 2014/11/16 20:03:13 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	int		i;
	int		max;
	char	j;

	i = 0;
	max = 0;
	while (s[max])
		max++;
	max--;
	while (i <= max / 2)
	{
		j = s[i];
		s[i] = s[max - i];
		s[max - i] = j;
		i++;
	}
	return (s);
}
