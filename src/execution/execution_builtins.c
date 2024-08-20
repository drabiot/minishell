/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:50:05 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/21 01:20:50 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtins(char *arg)
{
	int		return_value;

	return_value = 0;
	if (!arg)
		return (return_value);
	else if (ft_strcmp(arg, "cd") == 0)
		return_value = 1;
	else if (ft_strcmp(arg, "echo") == 0)
		return_value = 1;
	else if (ft_strcmp(arg, "env") == 0)
		return_value = 1;
	else if (ft_strcmp(arg, "exit") == 0)
		return_value = 1;
	else if (ft_strcmp(arg, "export") == 0)
		return_value = 1;
	else if (ft_strcmp(arg, "pwd") == 0)
		return_value = 1;
	else if (ft_strcmp(arg, "unset") == 0)
		return_value = 1;
	return (return_value);
}

int	ft_find_builtins(int fd, t_glob **t_envp, t_exec *exec)
{
	int		return_value;

	return_value = -1;
	if (!exec)
		return (0);
	else if (ft_strcmp(exec->cmd, "cd") == 0)
		return_value = ft_cd(exec, t_envp);
	else if (ft_strcmp(exec->cmd, "echo") == 0)
		return_value = ft_echo(fd, exec, *t_envp);
	else if (ft_strcmp(exec->cmd, "env") == 0)
		return_value = ft_env(fd, t_envp);
	else if (ft_strcmp(exec->cmd, "exit") == 0)
		ft_exit(exec, t_envp, &return_value);
	else if (ft_strcmp(exec->cmd, "export") == 0)
		return_value = ft_export(fd, *t_envp, exec);
	else if (ft_strcmp(exec->cmd, "pwd") == 0)
		return_value = ft_pwd(*t_envp, fd);
	else if (ft_strcmp(exec->cmd, "unset") == 0)
		return_value = ft_unset(t_envp, exec);
	(*t_envp)->utils->return_code = return_value;
	return (return_value);
}
