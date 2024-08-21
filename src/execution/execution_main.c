/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:36:16 by nberduck          #+#    #+#             */
/*   Updated: 2024/08/21 07:17:45 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_output(t_exec *exec)
{
	if (!exec->outfile[0] || exec->file_error == TRUE)
		return ;
	if (ft_strcmp(exec->outfile[1], "append") == 0)
		exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
				| O_APPEND, 0644);
	else if (ft_strcmp(exec->outfile[1], "trunc") == 0)
		exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
}

void	handle_input(t_exec *exec)
{
	if (exec->infile && exec->file_error == FALSE)
	{
		if (exec->fd_in != -1)
			close(exec->fd_in);
		exec->fd_in = open(exec->infile, O_RDONLY);
	}
}

void	create_pipe(t_exec *exec)
{
	int	fd_pipe[2];

	if (exec && exec->pos_cmd < exec->nb_cmd)
	{
		if (pipe(fd_pipe) == -1)
			return ;
		if (exec->outfile[0] && exec->file_error == FALSE)
		{
			handle_output(exec);
			if (exec->fd_out != 1)
				close(fd_pipe[1]);
		}
		if (exec->fd_out == -1)
			exec->fd_out = fd_pipe[1];
		if (exec->infile && exec->file_error == FALSE)
			exec->fd_in = open(exec->infile, O_RDONLY);
		exec->next->fd_in = fd_pipe[0];
	}
	else
	{
		handle_output(exec);
		handle_input(exec);
	}
}

int	handle_builtin_output(t_exec *exec, t_glob *t_envp)
{
	int	ret;

	if (exec->outfile[0])
	{
		if (ft_strcmp(exec->outfile[1], "append") == 0)
			exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		else if (ft_strcmp(exec->outfile[1], "trunc") == 0)
			exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
		else
			exec->fd_out = 1;
	}
	else
		exec->fd_out = 1;
	ret = ft_find_builtins(exec->fd_out, &t_envp, exec);
	if (ret != -1)
	{
		if (exec->fd_out == 1)
			exec->fd_out = -1;
		close_fds(exec);
		free_exec(exec);
		return (ret);
	}
	return (-1);
}

int	ft_execution_main(t_glob **t_envp, t_cmd *cmd)
{
	int		pipe_len;
	t_exec	*exec;
	int		ret;

	g_sig = 0;
	if (!cmd)
		return ((*t_envp)->utils->return_code);
	pipe_len = ft_pipe_len(cmd);
	exec = init_exec(cmd, *t_envp, pipe_len);
	free_t_cmd(cmd);
	ret = return_error(t_envp, exec, pipe_len);
	if (ret != 0)
		return (ret);
	if (pipe_len == 1 && is_builtins(exec->cmd))
	{
		ret = handle_builtin_output(exec, *t_envp);
		if (ret != -1)
			return (ret);
	}
	ret = start_exec(exec, t_envp);
	free_exec(exec);
	return (ret);
}
