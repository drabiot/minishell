/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:49:49 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/21 20:42:32 by tchartie         ###   ########.fr       */
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

static void	set_infile_here(int fd, char *limiter, char *base, t_glob *t_envp)
{
	char	*line;
	char	*f_line;

	line = NULL;
	f_line = NULL;
	line = readline("> ");
	if (!line)
		end_of_file(base);
	f_line = create_line(line);
	if (check_sign(t_envp, fd, f_line))
		return ;
	while (!(g_sig == SIGINT) && f_line && ft_strcmp(f_line, limiter) != 0)
	{
		ft_putstr_fd(f_line, fd);
		free(f_line);
		line = readline("> ");
		if (!line)
			end_of_file(base);
		f_line = create_line(line);
		if (check_sign(t_envp, fd, f_line))
			return ;
	}
	free(f_line);
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

void	open_heredoc(char *limiter, t_exec *exec, t_glob *t_envp, int i)
{
	char	*file_limit;
	char	*file;
	int		file_fd;

	g_sig = 0;
	file = NULL;
	file_limit = NULL;
	if (t_envp && t_envp->utils->failled_here == FALSE)
	{
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
		set_infile_here(file_fd, file_limit, limiter, t_envp);
		if (file_limit)
			free (file_limit);
	}
}
