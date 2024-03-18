/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:07:27 by tchartie          #+#    #+#             */
/*   Updated: 2023/11/02 16:32:40 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*
** Returns an integer less than, equal to, or greater than zero
** if the first n bytes of s1 is found
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*sent1;
	unsigned char	*sent2;

	i = 0;
	sent1 = (void *)s1;
	sent2 = (void *)s2;
	while (n > i)
	{
		if (sent1[i] != sent2[i])
			return (sent1[i] - sent2[i]);
		i++;
	}
	return (0);
}
