/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:50:05 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/17 23:32:02 by tchartie         ###   ########.fr       */
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

int	ft_find_builtins(int fd, t_glob **t_envp, t_cmd *cmd)
{
	int		return_value;

	return_value = -1;
	if (!cmd)
		return (0);
	else if (ft_strcmp(cmd->arg, "cd") == 0)
		return_value = ft_cd(cmd, t_envp);
	else if (ft_strcmp(cmd->arg, "echo") == 0)
		return_value = ft_echo(fd, cmd, *t_envp);
	else if (ft_strcmp(cmd->arg, "env") == 0)
		return_value = ft_env(fd, t_envp);
	else if (ft_strcmp(cmd->arg, "exit") == 0)
	{
		return_value = ft_exit(fd, cmd, t_envp); // Have to do exit
		(*t_envp)->utils->return_code = return_value;
		exit (return_value);
	}
	else if (ft_strcmp(cmd->arg, "export") == 0)
		return_value = ft_export(fd, *t_envp, cmd);
	else if (ft_strcmp(cmd->arg, "pwd") == 0)
		return_value = ft_pwd(*t_envp);
	else if (ft_strcmp(cmd->arg, "unset") == 0)
		return_value = ft_unset(t_envp, cmd);
	(*t_envp)->utils->return_code = return_value;
	return (return_value);
}
