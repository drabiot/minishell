/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:36:16 by nberduck          #+#    #+#             */
/*   Updated: 2024/07/09 14:52:50 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_find_redir(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == APPEND_REDIR)
			return (1);
		if (tmp->type == TRUNC_REDIR)
			return (2);
		if (tmp->type == INPUT)
			return (3);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_execution_cmd(int fd, t_glob **t_envp, t_cmd *cmd)
{
	pid_t	pid;
	int		return_value;
	int		ret;

	return_value = ft_find_builtins_part1(fd, t_envp, cmd);
	if (return_value != -1)
		return (return_value);
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
			else if (return_value == 3)
				return_value = ft_input_redir(t_envp, cmd);
			else
				return_value = ft_execute_other_cmd(t_envp, cmd);
		}
		exit(return_value);
	}
	waitpid(pid, &ret, 0);
	ret = WEXITSTATUS(ret);
	(*t_envp)->utils->return_code = ret;
	printf("ret: %d, code: %d\n", ret, (*t_envp)->utils->return_code);
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
		return_value = ft_execution_cmd(1, t_envp, cmd);
		return (return_value);
	}
	return (1);
}
