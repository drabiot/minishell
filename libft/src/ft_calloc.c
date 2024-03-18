/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:39:15 by tchartie          #+#    #+#             */
/*   Updated: 2023/11/03 11:36:59 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*
** Allocates size bytes and returns a pointer
** to the allocated memory
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*tab;
	size_t			len;

	len = nmemb * size;
	if (len > 2147483647 || (nmemb > 65535 && size > 65535))
		return (NULL);
	tab = (unsigned char *)malloc(len);
	if (tab == 0)
		return (NULL);
	ft_bzero(tab, len);
	return (tab);
}
