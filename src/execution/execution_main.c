/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:36:16 by nberduck          #+#    #+#             */
/*   Updated: 2024/06/19 19:57:45 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_find_redir(t_cmd *cmd)
{
	t_cmd *tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == APPEND_REDIR)
			return (1);
		if (tmp->type == TRUNC_REDIR)
			return (2);
		tmp = tmp->next;
	}
	return (0);
}

// static t_cmd *ft_find_here_doc(t_cmd *cmd)
// {
// 	t_cmd	*tmp;
// 	t_cmd	*return_cmd;
// 	t_cmd	*limiter_cmd;

// 	tmp = cmd;
// 	while (tmp && tmp->next && tmp->next->next)
// 	{
// 		if (tmp->next->type == HERE_DOC && tmp->next->next->type == LIMITER)
// 		{
// 			return_cmd = ft_lstnmap_cmd(cmd, 1);
// 			limiter_cmd = return_cmd->next->next;
// 			// ft_lstdelone_cmd(return_cmd->next);
// 			return_cmd->next = limiter_cmd;
// 			return(return_cmd);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return(NULL);
// }

int	ft_execution_cmd(int fd, t_glob **t_envp, t_cmd *cmd)
{
	pid_t	pid;
	int		return_value;
	
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		if (ft_have_heredoc(cmd))
			return_value = ft_here_doc(t_envp, cmd);
		else
		{
			return_value = ft_find_redir(cmd);
			if (return_value == 1)
				return_value = ft_append_redir(t_envp, cmd);
			else if (return_value == 2)
				return_value = ft_trunc_redir(t_envp, cmd);
			else
			{	
				return_value = ft_find_builtins_part1(fd, t_envp, cmd);
				if (return_value == -1)
					return_value = ft_execute_other_cmd(t_envp, cmd);
			}
		}
		return (return_value);
	}
	waitpid(pid, NULL, 0);
	return (0);
}
// int	ft_start_execution(int fd, t_glob **t_envp, t_cmd *cmd, int npipe)
// {
// 	int		return_value;
// 	int		other_function;
// 	t_cmd	*start;
// 	pid_t	pid;
	
// 	pid = fork();
// 	if (pid < 0)
// 		return (1);
// 	if (pid == 0)
// 	{
// 		start = ft_find_here_doc(cmd);
// 		if (start)
// 			ft_here_doc(t_envp, start);
// 		else if (cmd && cmd->type == COMMAND)
// 		{
// 			start = ft_lstnmap_cmd(cmd, npipe);
// 			other_function = ft_find_redir(start);
// 			// printf("%s,%s,%s\n", start->arg, start->next->arg, start->next->next->arg);
// 			if (other_function == 1)
// 				ft_append_redir(t_envp, start);
// 			else if (other_function == 2)
// 				ft_trunc_redir(t_envp, start);
// 			else
// 			{
// 				return_value = ft_find_builtins_part1(fd, t_envp, start);
// 				if (return_value == -1)
// 					return_value = ft_execute_other_cmd(t_envp, start);
// 			}
// 			// ft_lstclear_cmd(&start);
// 			return (return_value);
// 		}
// 	}
// 	waitpid(pid, NULL, 0);
// 	return (0);
// }

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
		return_value = ft_execution_cmd(1, t_envp, cmd);
		return (return_value);
	}
	return (1);
}
