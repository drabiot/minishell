/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:01:10 by tchartie          #+#    #+#             */
/*   Updated: 2023/11/01 18:45:41 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*
** Compares the two given strings & returns an integer
** indicating the result of the comparison
**  •0, if the s1 and s2 are equal
**  •a negative value if s1 is less than s2
**  •a positive value if s1 is greater than s2
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*sent1;
	unsigned char	*sent2;

	i = 0;
	if (!s1 || !s2)
		return (0);
	sent1 = (void *)s1;
	sent2 = (void *)s2;
	while (((sent1[i] || sent2[i]) && (sent1[i] - sent2[i] == 0)) && (n > i))
		i++;
	if (n == i)
		return (0);
	return (sent1[i] - sent2[i]);
}
