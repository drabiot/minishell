/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:49:49 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/21 01:18:14 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	generate_key_random(void)
{
	int		pid;

	pid = fork();
	if (pid == 0)
		exit(0);
	ft_srand(pid);
}

static char	*create_line(char *line)
{
	char	*finish_line;

	finish_line = NULL;
	if (line)
	{
		finish_line = ft_strjoin(line, "\n");
		free(line);
		line = NULL;
	}
	return (finish_line);
}

static void	set_infile_here(int fd, char *limiter, char *base_limiter)
{
	char	*line;
	char	*finish_line;

	line = NULL;
	finish_line = NULL;
	line = readline("> ");
	if (!line)
		end_of_file(base_limiter);
	finish_line = create_line(line);
	while (finish_line && ft_strcmp(finish_line, limiter) != 0)
	{
		ft_putstr_fd(finish_line, fd);
		free(finish_line);
		line = readline("> ");
		if (!line)
			end_of_file(base_limiter);
		finish_line = create_line(line);
	}
	if (finish_line)
		free(finish_line);
	if (fd >= 3)
		close(fd);
}

static void	modif_infile(t_exec *exec, char *file)
{
	if (!exec->file_error)
	{
		if (exec->infile)
			free(exec->infile);
		exec->infile = ft_strdup(file);
	}
}

void	open_heredoc(char *limiter, t_exec *exec)
{
	char	*file_limit;
	char	*file;
	int		file_fd;
	int		i;

	i = 0;
	file = NULL;
	file_limit = NULL;
	check_file(&file_limit, &file, &file_fd, limiter);
	while (exec->name_heredoc[i])
		i++;
	if (i < 16)
		exec->name_heredoc[i] = file;
	else
	{
		if (file_fd >= 3)
			close(file_fd);
		unlink(file);
	}
	modif_infile(exec, file);
	set_infile_here(file_fd, file_limit, limiter);
	if (file_limit)
		free (file_limit);
}
