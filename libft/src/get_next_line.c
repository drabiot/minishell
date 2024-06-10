/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:48:25 by nberduck          #+#    #+#             */
/*   Updated: 2024/06/09 21:40:23 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_read_line(int fd)
{
	int		bytes;
	char	*buff;

	buff = malloc(BUFFER_SIZE);
	if (!buff)
		return (NULL);
	bytes = read(fd, buff, BUFFER_SIZE);
	if (!bytes || bytes == -1)
	{
		free(buff);
		return (NULL);
	}
	buff = ft_substr_gnl(buff, 0, bytes, 1);
	return (buff);
}

char	*ft_div_line(char *current_line, char *last_line, int i)
{
	if (current_line[i + 1])
		last_line = ft_substr_gnl(current_line, i + 1,
				ft_strlen(&current_line[i + 1]), 0);
	else if (current_line && last_line)
	{
		free(last_line);
		last_line = NULL;
	}
	return (last_line);
}

char	*ft_find_line(char *current_line, char **last_line, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (current_line[i])
	{
		if (current_line[i] == '\n')
		{
			*last_line = ft_div_line(current_line, *last_line, i);
			current_line = ft_substr_gnl(current_line, 0, i + 1, 1);
			break ;
		}
		if (current_line[i + 1] == 0)
		{
			line = ft_read_line(fd);
			if (!line)
				break ;
			current_line = ft_strjoin_gnl(current_line, line);
		}
		i++;
	}
	return (current_line);
}

char	*ft_find_readed_line(char **last_line)
{
	int		len_last_line;
	char	*current_line;

	if (last_line && ft_find_newline(*last_line) != -1)
	{
		len_last_line = ft_find_newline(*last_line);
		current_line = ft_substr_gnl(*last_line, 0, len_last_line + 1, 0);
		if (*last_line && last_line[0][len_last_line + 1])
			*last_line = ft_substr_gnl(*last_line, len_last_line + 1,
					ft_strlen(&last_line[0][len_last_line + 1]), 1);
		else
		{
			free(*last_line);
			*last_line = NULL;
		}
		return (current_line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*last_line = NULL;
	char		*current_line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1)
		return (NULL);
	current_line = ft_find_readed_line(&last_line);
	if (current_line)
		return (current_line);
	current_line = ft_read_line(fd);
	if (!current_line && !last_line)
		return (NULL);
	if (!current_line && last_line)
	{
		current_line = ft_substr_gnl(last_line, 0, ft_strlen(last_line), 1);
		last_line = NULL;
		return (current_line);
	}
	if (last_line && last_line)
	{
		current_line = ft_strjoin_gnl(last_line, current_line);
		last_line = NULL;
	}
	current_line = ft_find_line(current_line, &last_line, fd);
	return (current_line);
}
