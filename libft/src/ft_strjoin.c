/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:05:24 by tchartie          #+#    #+#             */
/*   Updated: 2024/06/19 18:54:51 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*
** Allocates & returns a new string,
** which is the result of the concatenation
** of ’s1’ and ’s2’
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buffer;
	size_t	len_s1;
	size_t	len_s2;

	len_s2 = ft_strlen(s2);
	if (!s1)
		buffer = (char *)malloc(sizeof(char) * (len_s2 + 1));
	else
	{
		len_s1 = ft_strlen(s1);
		buffer = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	}
	if (!buffer)
		return (NULL);
	buffer = ft_strcat(s1, s2, buffer);
	return (buffer);
}
