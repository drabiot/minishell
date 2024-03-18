/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:58:23 by tchartie          #+#    #+#             */
/*   Updated: 2023/11/07 13:24:29 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*
** Copies n bytes from memory area src to memory area dest
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	if (!dest && !src)
		return (NULL);
	d = dest;
	s = (char *)src;
	while (i < n)
	{
		*d = *s;
		i++;
		d++;
		s++;
	}
	return (dest);
}
