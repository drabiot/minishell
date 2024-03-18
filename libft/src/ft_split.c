/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:04:17 by tchartie          #+#    #+#             */
/*   Updated: 2023/11/07 13:36:16 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*
** Free the given matrix
*/
static char	**free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

/*
** Count numbers of word (a word is consider like that when surround 
** by separators or when there starting or finishing a string) of 
** given string
*/
static size_t	count_word(char const *s, char sep)
{
	size_t	nb_word;

	nb_word = 0;
	while (*s)
	{
		while (*s == sep)
			s++;
		if (*s)
			nb_word++;
		while (*s != sep && *s)
			s++;
	}
	return (nb_word);
}

/*
** Fill given matrix with given arguments
*/
static char	**fill_array(char const *s, char c, char **array)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				len = ft_strlen(s);
			else
				len = ft_strchr(s, c) - s;
			array[i] = ft_substr(s, 0, len);
			if (!array)
				return (free_array(array));
			i++;
			s += len;
		}
	}
	array[i] = NULL;
	return (array);
}

/*
** Allocates & returns an array
** of strings obtained by splitting ’s’ using the
** character ’c’ as a delimiter. The array must end
** with a NULL pointer
*/
char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s)
		return (0);
	array = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array = fill_array(s, c, array);
	return (array);
}
