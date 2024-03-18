/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:08:43 by tchartie          #+#    #+#             */
/*   Updated: 2023/11/02 16:25:26 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*
** Scans the initial n bytes of the memory area
** pointed to by s for the first instance of c
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*found;

	i = 0;
	found = (unsigned char *)s;
	while (i < n)
	{
		if (found[i] == (unsigned char)c)
			return ((void *)found + i);
		i++;
	}
	return (NULL);
}
