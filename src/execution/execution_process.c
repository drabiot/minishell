/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:31:43 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/21 02:22:19 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_file_error(t_exec *list, t_glob *t_envp, t_exec *exec)
{
	int	ret_execve;
	int	cmd;

	(void)exec;
	ret_execve = 0;
	cmd = 1;
	if (exec)
		cmd = exec->nb_cmd;
	if (t_envp)
		ret_execve = t_envp->utils->return_code;
	free_exit(list, t_envp);
	if (cmd >= 2)
		exit(1);
	else
		exit(ret_execve);
}

void	handl_fail(t_exec *list, t_glob *t_env, t_exec *exe, struct stat s_stt)
{
	if (ft_strchr(exe->base_cmd, '/'))
	{
		free_exit(list, t_env);
		if (errno == EACCES && (s_stt.st_mode & __S_IFMT) == __S_IFDIR)
		{
			ft_putstr_fd(" Is a directory\n", 2);
			exit (126);
		}
		ft_errno();
		if (errno == EACCES)
			exit(126);
		exit(127);
	}
	else
	{
		ft_putstr_fd(" command not found\n", 2);
		free_exit(list, t_env);
	}
	exit(127);
}

void	init_process(t_exec *list, t_exec *exec, t_glob **t_envp)
{
	exec->pid = fork();
	ft_signal(2);
	if (exec->pid == -1)
		return ;
	else if (exec->pid == 0)
		process(exec, list, t_envp);
}

void	validate_base_cmd(t_exec *list, t_glob *t_envp, t_exec *exec)
{
	if (!exec->base_cmd)
	{
		handle_error_quit(list, &t_envp, 0, NULL);
		return ;
	}
	if (exec->base_cmd[0] == '\0')
	{
		handle_error_quit(list, &t_envp, 127, " command not found\n");
		return ;
	}
	if (exec->base_cmd[0] == '.' && list->base_cmd[1] == '\0')
	{
		handle_error_quit(list, &t_envp, 2, " filename argument required\n");
		return ;
	}
}

void	process(t_exec *exec, t_exec *list, t_glob **t_envp)
{
	int			ret_execve;
	struct stat	s_stat;

	dup2(exec->fd_in, STDIN_FILENO);
	dup2(exec->fd_out, STDOUT_FILENO);
	ret_execve = 0;
	close_fds(list);
	validate_base_cmd(list, *t_envp, exec);
	stat(list->cmd, &s_stat);
	if (exec->file_error == TRUE)
		handle_file_error(list, *t_envp, exec);
	if (is_builtins(exec->cmd))
	{
		ret_execve = ft_find_builtins(STDOUT_FILENO, t_envp, exec);
		handle_error_quit(list, t_envp, ret_execve, NULL);
	}
	else if (exec->flags)
	{
		rl_clear_history();
		ret_execve = execve(exec->cmd, exec->flags, (*t_envp)->utils->env);
	}
	else
		handle_error_quit(list, t_envp, 0, NULL);
	if (ret_execve == -1)
		handl_fail(list, *t_envp, exec, s_stat);
}
