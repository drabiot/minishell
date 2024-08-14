/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:49:49 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/14 17:40:10 by adorlac          ###   ########.fr       */
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
		//error malloc
	}
	while (*file_fd == -1)
	{
		tmp_file = generate_rd_file(tmp_file);
		*file_fd = open(tmp_file, O_EXCL | O_WRONLY | O_CREAT, 0644);
	}
	return (tmp_file);
}

static void	set_infile(int fd, char *limiter)
{
	char	*line;

	line = NULL;
	line = readline("> ");
	line = ft_strjoin(line, "\n");
	while (line && ft_strcmp(line, limiter) != 0)
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = readline("> ");
		line = ft_strjoin(line, "\n");
	}
	if (line)
		free(line);
}

void	open_heredoc(char *limiter, t_exec *exec, char *file, char *path)
{
	char	*file_limit;
	int		file_fd;

	file_limit = NULL;
	file_limit = ft_strjoin(limiter, "\n");
	if (!file_limit)
	{
		ft_putstr_fd(" Failled Malloc\n", 2);
		//error malloc
	}
	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_putstr_fd(" Failled to create Here_doc\n", 2);
		return ;
	}
	file = create_rd_file(&file_fd);
	if (!exec->file_error)
	{
		//exec->fd_in = file_fd;
		exec->infile = file;
	}
	set_infile(file_fd, file_limit);
	//if (!unlink(file))
	//	 ft_putstr_fd(" Failled to destroy tmp file\n", 2);
	if (file_limit)
		free (file_limit);
}
