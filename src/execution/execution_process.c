/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:31:43 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/20 15:27:19 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*void handle_execve_failure(t_list *list, t_glob *t_envp, t_exec *exec, struct s_stat s_stat)
{
    if (ft_strchr(exec->base_cmd, '/')) {
        free_exit(list, t_envp);
        if (errno == EACCES && (s_stat.st_mode & __S_IFMT) == __S_IFDIR)
        {
            ft_putstr_fd(" Is a directory\n", 2);
            exit(126);
        }
        ft_errno();  // Appelle une fonction pour définir l'errno
        if (errno == EACCES)
            exit(126);
        exit(127);
    }
    else
    {
        ft_putstr_fd(" command not found\n", 2);
        free_exit(list, t_envp);
    }
    exit(127);
}*/

void	init_process(t_exec *list, t_exec *exec, t_glob **t_envp)
{
	exec->pid = fork();
	ft_signal(2);
	if (exec->pid == -1)
		return ;
	else if (exec->pid == 0)
		process(exec, list, t_envp);
}

void	process(t_exec *exec, t_exec *list, t_glob **t_envp)
{
	int		ret_execve;
	struct stat	s_stat;

	dup2(exec->fd_in, STDIN_FILENO);
	dup2(exec->fd_out, STDOUT_FILENO);
	ret_execve = 0;
	close_fds(list);
	if (!exec->base_cmd)
	{
		free_exit(list, *t_envp);
		exit(0);
	}
	if (exec->base_cmd[0] == '\0')
	{
		free_exit(list, *t_envp);
		ft_putstr_fd(" command not found\n", 2);
		exit (127);
	}
	if (exec->base_cmd[0] == '.' && list->base_cmd[1] == '\0')
	{
		free_exit(list, *t_envp);
		ft_putstr_fd(" filename argument required\n", 2);
		exit(2);
	}
	stat(list->cmd, &s_stat);
	if (exec->file_error == TRUE)
	{
		ret_execve = (*t_envp)->utils->return_code;
		if (exec->nb_cmd >= 2)
		{
			free_exit(list, *t_envp);
			exit (1);
		}
		else
		{
			free_exit(list, *t_envp);
			exit(ret_execve);
		}
	}
	if (is_builtins(exec->cmd))
	{
		ret_execve = ft_find_builtins(STDOUT_FILENO, t_envp, exec);
		free_exit(list, *t_envp);
		exit(ret_execve);
	}
	else if (exec->flags)
	{
		rl_clear_history();
		ret_execve = execve(exec->cmd, exec->flags, (*t_envp)->utils->env);
	}
	else
	{
		free_exit(list, *t_envp);
		exit(0);
	}
	if (ret_execve == -1)
/*		handle_execve_failure(list, *t_envp, exec, s_stat);*/
	{
		if (ft_strchr(exec->base_cmd, '/')) {
			//ft_errno();
			free_exit(list, *t_envp);
			if (errno == EACCES && (s_stat.st_mode & __S_IFMT) == __S_IFDIR)
			{
				ft_putstr_fd(" Is a directory\n", 2);
				exit (126);
			}
			ft_errno();
			if(errno == EACCES)
				exit(126);
			exit(127);
		}
		else
		{
			ft_putstr_fd(" command not found\n", 2);
			free_exit(list, *t_envp);
		}
		exit(127);
	}
}
