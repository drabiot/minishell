/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:08:29 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/09 15:15:45 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*
 * See if there a newline in the string
 */

int	new_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

/*
 * If check_nl == 0 : Copy the source until he see a newline to destination
 * If check_nl != 0 : Copy the source to destination
 */

char	*ft_strcpy(char *dst, const char *src, int check_nl)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (check_nl == 0)
	{
		while (src[i] != '\n' && src[i])
			dst[j++] = src[i++];
		if (src[i] == '\n')
			dst[j++] = src[i++];
	}
	else if (check_nl != 0)
	{
		while (src[i])
			dst[j++] = src[i++];
	}
	dst[i] = '\0';
	return (dst);
}
