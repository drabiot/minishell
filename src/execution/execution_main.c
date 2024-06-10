/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:36:16 by nberduck          #+#    #+#             */
/*   Updated: 2024/06/10 11:38:48 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd *ft_find_here_doc(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*return_cmd;
	t_cmd	*limiter_cmd;

	tmp = cmd;
	while (tmp && tmp->next && tmp->next->next)
	{
		if (tmp->next->type == HERE_DOC && tmp->next->next->type == LIMITER)
		{
			return_cmd = ft_lstnmap_cmd(cmd, 1);
			limiter_cmd = return_cmd->next->next;
			ft_lstdelone_cmd(return_cmd->next);
			return_cmd->next = limiter_cmd;
			return(return_cmd);
		}
		tmp = tmp->next;
	}
	return(NULL);
}
int	ft_start_execution(int fd, t_glob **t_envp, t_cmd *cmd, int npipe)
{
	int		return_value;
	t_cmd	*start;
	pid_t	pid;
	
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		start = ft_find_here_doc(cmd);
		if (start)
			ft_here_doc(t_envp, start);
		else if (cmd && cmd->type == COMMAND)
		{
			start = ft_lstnmap_cmd(cmd, npipe);
			return_value = ft_find_builtins_part1(fd, t_envp, start);
			if (return_value == -1)
			{
				return_value = ft_execute_other_cmd(t_envp, start);
			}
			// ft_lstclear_cmd(&start);
			return (return_value);
		}
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int	ft_execution_main(t_glob **t_envp, t_cmd *cmd)
{
	// printf("%s\n", "t");
	int		pipe_len;
	int		return_value;

	pipe_len = ft_pipe_len(cmd);
	if (pipe_len != 1)
	{
		// return_value =
		// return_value = ft_execution_pipe_main(t_envp, cmd, pipe_len);
		// return (return_value);
	}
	else
	{
		return_value = ft_start_execution(1, t_envp, cmd, 1);
		return (return_value);
	}
	return (1);
}
