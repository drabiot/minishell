/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:36:16 by nberduck          #+#    #+#             */
/*   Updated: 2024/08/20 15:44:25 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_fds(t_exec *list)
{
	while (list)
	{
		if (list->fd_in != -1)
			close(list->fd_in);
		list->fd_in = -1;
		if (list->fd_out != -1)
			close(list->fd_out);
		list->fd_out = -1;
		list = list->next;
	}
}

static int	wait_all_pid(t_exec *list)
{
	int	ret;

	ret = 0;
	while (list->next)
	{
		waitpid(list->pid, NULL, 0);
		list = list->next;
	}
	waitpid(list->pid, &ret, 0);
	if (WIFEXITED(ret))
		ret = WEXITSTATUS(ret);
	else if (WIFSIGNALED(ret))
		ret = WTERMSIG(ret) + 128;
	return (ret);
}

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
	if (exec->outfile[0] && ft_strcmp(exec->outfile[1], "append") == 0 && exec->file_error == FALSE)
		exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
			| O_APPEND, 0644);
	else if (exec->outfile[0] && ft_strcmp(exec->outfile[1], "trunc") == 0 && exec->file_error == FALSE)
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
	// t_exec *tmp = exec;
	// while (tmp)
	// {
	// 	printf("EXEC:\nnb_cmd: %d\npos_cmd: %d\ninfile: %s\noutfile: %s, type: %s\ncmd: %s\nflags: %s %s\nheredoc: %d\nlimiter: %s\nfd_in: %d      fd_out: %d\n", tmp->nb_cmd, tmp->pos_cmd, tmp->infile, tmp->outfile[0], tmp->outfile[1], tmp->cmd, tmp->flags[0], tmp->flags[1], tmp->have_heredoc, tmp->limiter, tmp->fd_in, tmp->fd_out);
	// 	tmp = tmp->next;
	// }
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
	//close_fds(exec);
	// t_exec *tmp = exec;
	// while (tmp)
	// {
	// 	printf("EXEC:\nnb_cmd: %d\npos_cmd: %d\ninfile: %s\noutfile: %s, type: %s\ncmd: %s\nflags: %s %s\nheredoc: %d\nfd_in: %d      fd_out: %d\n", tmp->nb_cmd, tmp->pos_cmd, tmp->infile, tmp->outfile[0], tmp->outfile[1], tmp->cmd, tmp->flags[0], tmp->flags[1], tmp->have_heredoc, tmp->fd_in, tmp->fd_out);
	// 	tmp = tmp->next;
	// }
	free_exec(exec);
	//clean t_exec
	return (ret);
}

