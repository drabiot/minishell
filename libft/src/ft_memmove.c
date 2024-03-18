/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:09:20 by tchartie          #+#    #+#             */
/*   Updated: 2023/11/07 13:25:12 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*
** Copies n bytes from memory area src to memory area dest
*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*area_dest;
	char	*area_src;

	i = 0;
	if (!dest && !src)
		return (NULL);
	area_dest = dest;
	area_src = (void *)src;
	if (src < dest)
	{
		while (n > 0)
		{
			area_dest[n - 1] = area_src[n - 1];
			n--;
		}
		return (dest);
	}
	while (i < n)
	{
		area_dest[i] = area_src[i];
		i++;
	}
	return (dest);
}
