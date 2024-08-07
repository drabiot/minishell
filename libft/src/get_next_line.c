/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:08:18 by tchartie          #+#    #+#             */
/*   Updated: 2024/06/13 19:58:46 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*
 * Take a file descriptor & copy the content to a stash
 */

char	*read_buff(int fd, char *stash)
{
	char	*buff;
	int		reading;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	reading = 1;
	if (!buff)
		return (NULL);
	while (!new_line(stash) && reading != 0)
	{
		reading = (int)read(fd, buff, BUFFER_SIZE);
		if ((!stash && reading == 0) || reading == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[reading] = '\0';
		stash = ft_strjoin(stash, buff);
	}
	free(buff);
	return (stash);
}

/*
 * Take the stash and copy its content until he detect a newline
 */

char	*add_to_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line = ft_strcpy(line, stash, 0);
	return (line);
}

/*
 * clean the stash of what he added in add_to_line()
 */

char	*clean_stash(char *stash)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	if (!stash || !stash[0])
	{
		free(stash);
		return (NULL);
	}
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	len = ft_strlen(stash) - i;
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	tmp = ft_strcpy(tmp, &stash[i], 1);
	free(stash);
	return (tmp);
}

/*
 * Take a file descriptor & return the line we wanted
 */

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_buff(fd, stash[fd]);
	line = add_to_line(stash[fd]);
	stash[fd] = clean_stash(stash[fd]);
	if (!stash[fd] && !line)
	{
		free(stash[fd]);
		return (NULL);
	}
	return (line);
}
