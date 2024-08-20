/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:36:16 by nberduck          #+#    #+#             */
/*   Updated: 2024/08/20 16:46:05 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	create_pipe(t_exec *exec)
{
	int		pipe_ret;
	int		fd_pipe[2];
	t_exec	*list;

	list = NULL;
	if (exec)
		list = exec;
	while (exec->next)
	{
		pipe_ret = pipe(fd_pipe);
		if (pipe_ret == -1)
			return ;
		if (exec->outfile[0] && exec->file_error == FALSE)
		{
			if (ft_strcmp(exec->outfile[1], "append") == 0)
				exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
						| O_APPEND, 0644);
			else if (ft_strcmp(exec->outfile[1], "trunc") == 0)
				exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
						| O_TRUNC, 0644);
			if (exec->fd_out != -1)
				close(fd_pipe[1]);
		}
		if (exec->fd_out == -1)
			exec->fd_out = fd_pipe[1];
		if (exec->infile && exec->file_error == FALSE)
			exec->fd_in = open(exec->infile, O_RDONLY);
		exec->next->fd_in = fd_pipe[0];
		exec = exec->next;
	}
	if (exec->outfile[0] && ft_strcmp(exec->outfile[1], "append") == 0
		&& exec->file_error == FALSE)
		exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
				| O_APPEND, 0644);
	else if (exec->outfile[0] && ft_strcmp(exec->outfile[1], "trunc") == 0
		&& exec->file_error == FALSE)
		exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
	if (exec->infile && exec->file_error == FALSE)
	{
		if (exec->fd_in != -1)
			close(exec->fd_in);
		exec->fd_in = open(exec->infile, O_RDONLY);
	}
}

int	start_exec(t_exec *exec, t_glob **t_envp)
{
	int		ret;
	t_exec	*list;

	ret = 0;
	list = NULL;
	create_pipe(exec);
	if (exec)
		list = exec;
	while (exec)
	{
		init_process(list, exec, t_envp);
		exec = exec->next;
	}
	close_fds(list);
	ret = wait_all_pid(list);
	return (ret);
}

int	ft_execution_main(t_glob **t_envp, t_cmd *cmd)
{
	int		pipe_len;
	t_exec	*exec;
	int		ret;

	if (!cmd)
		return ((*t_envp)->utils->return_code);
	pipe_len = ft_pipe_len(cmd);
	exec = init_exec(cmd, *t_envp, pipe_len);
	ret = 0;
	free_t_cmd(cmd);
	if (pipe_len == 1 && exec->file_error == TRUE)
	{
		free_exec(exec);
		return (1);
	}
	if (pipe_len == 1 && is_builtins(exec->cmd))
	{
		if (exec->outfile[0] && ft_strcmp(exec->outfile[1], "append") == 0)
			exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		else if (exec->outfile[0] && ft_strcmp(exec->outfile[1], "trunc") == 0)
			exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
		else
			exec->fd_out = 1;
		ret = ft_find_builtins(exec->fd_out, t_envp, exec);
		if (ret != -1)
		{
			if (exec->fd_out == 1)
				exec->fd_out = -1;
			close_fds(exec);
			free_exec(exec);
			return (ret);
		}
	}
	ret = start_exec(exec, t_envp);
	free_exec(exec);
	return (ret);
}
