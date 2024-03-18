/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:46:09 by tchartie          #+#    #+#             */
/*   Updated: 2023/11/07 13:31:54 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*
** Locates the first occurence of the null-terminated string big,
** where not more than len characters are searched
*/
char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	find_length;

	i = 0;
	if ((!s1 || !s2) && len == 0)
		return (NULL);
	find_length = ft_strlen(s2);
	if (find_length == 0)
		return ((char *)s1);
	while (s1[i] && i < len)
	{
		j = 0;
		while (j < find_length && s1[i + j] == s2[j] && i + j < len)
			j++;
		if (j == find_length)
			return ((char *)&s1[i]);
		i++;
	}
	return (NULL);
}
