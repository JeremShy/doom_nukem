/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 11:40:35 by alanteri          #+#    #+#             */
/*   Updated: 2014/11/12 13:12:35 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*memzone;

	memzone = (char *)malloc(sizeof(char) * size);
	if (memzone == NULL)
		return (NULL);
	ft_bzero(memzone, size);
	return (memzone);
}
