/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:48:21 by nberduck          #+#    #+#             */
/*   Updated: 2024/06/09 21:40:07 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_substr_gnl(char *s, int start, int len, int clear)
{
	char	*finalstr;
	int		i;

	if (!s)
		return (NULL);
	finalstr = malloc((len + 1) * sizeof(char));
	if (!finalstr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		finalstr[i] = s[start + i];
		i++;
	}
	finalstr[i] = 0;
	if (clear == 1)
		free(s);
	return (finalstr);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char			*finalstr;
	unsigned int	finallen;
	unsigned int	i;
	unsigned int	j;

	if (!s1 || !s2)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	i = -1;
	j = -1;
	finallen = ft_strlen(s1) + ft_strlen(s2);
	finalstr = malloc((finallen + 1) * sizeof(char));
	if (!finalstr)
		return (NULL);
	while (s1[++i])
		finalstr[i] = s1[i];
	while (s2[++j])
		finalstr[i + j] = s2[j];
	finalstr[i + j] = 0;
	free(s1);
	free(s2);
	return (finalstr);
}

char	ft_find_newline(char *last_line)
{
	int	i;

	i = 0;
	while (last_line && last_line[i])
	{
		if (last_line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
