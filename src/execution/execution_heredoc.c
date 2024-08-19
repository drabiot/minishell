/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:49:49 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/19 22:37:24 by tchartie         ###   ########.fr       */
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

static void	set_infile(int fd, char *limiter)
{
	char	*line;

	line = NULL;
	line = readline("> ");
	if (line)
		line = ft_strjoin(line, "\n");
	while (line && ft_strcmp(line, limiter) != 0)
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = readline("> ");
		if (line)
			line = ft_strjoin(line, "\n");
	}
	if (line)
		free(line);
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
	set_infile(file_fd, file_limit);
	if (file_limit)
		free (file_limit);
}
