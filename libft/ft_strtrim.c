/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanteri <alanteri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 15:31:41 by alanteri          #+#    #+#             */
/*   Updated: 2014/11/14 21:37:42 by alanteri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	char	*new;
	int		start;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	start = i;
	while (s[i])
		i++;
	i--;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && i >= 0)
		i--;
	(i < start) ? start = i : i;
	new = (char *)malloc(sizeof(char) * (i - start + 2));
	if (new == NULL)
		return (NULL);
	j = -1;
	while (start + ++j <= i)
		new[j] = (char)s[j + start];
	new[j] = '\0';
	return (new);
}
