/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 22:26:33 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/21 01:24:51 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_have_heredoc(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->type == HERE_DOC)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

static char	*generate_rd_file(char *tmp_file)
{
	int		c_rand;
	char	*suff;
	char	*final_file;

	c_rand = ft_rand(0, 51);
	suff = ft_substr("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
			c_rand, 1);
	final_file = ft_strjoin(tmp_file, suff);
	if (tmp_file)
		free(tmp_file);
	if (suff)
		free(suff);
	return (final_file);
}

static char	*create_rd_file(int *file_fd)
{
	char	*tmp_file;

	tmp_file = ft_strdup("tmp_");
	*file_fd = -1;
	if (!tmp_file)
	{
		ft_putstr_fd(" Failled Malloc\n", 2);
		return (NULL);
	}
	while (*file_fd == -1)
	{
		tmp_file = generate_rd_file(tmp_file);
		*file_fd = open(tmp_file, O_EXCL | O_WRONLY | O_CREAT, 0644);
	}
	return (tmp_file);
}

t_bool	check_file(char **file_limit, char **file, int *file_fd, char *limiter)
{
	*file_limit = ft_strjoin(limiter, "\n");
	if (!(*file_limit))
	{
		ft_putstr_fd(" Failled Malloc\n", 2);
		return (FALSE);
	}
	*file = create_rd_file(file_fd);
	if (!*file)
	{
		if (*file_limit)
			free(*file_limit);
		return (FALSE);
	}
	return (TRUE);
}

void	end_of_file(char *limiter)
{
	ft_putstr_fd("warning: here-document delimited \
by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
}
