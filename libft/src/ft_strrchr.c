/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:39:58 by tchartie          #+#    #+#             */
/*   Updated: 2023/11/08 16:16:36 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*
** Returns a pointer to the last occurence of
** the character c in the string s
*/
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	c = (char)c;
	if (!ft_isascii(c))
		return ((char *) s);
	while (s[i])
		i++;
	if (c == 0)
		return ((char *)&s[i]);
	while (i >= 0)
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
