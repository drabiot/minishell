/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:50:05 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/16 22:44:41 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_find_builtins(int fd, t_glob **t_envp, t_cmd *cmd)
{
	int		return_value;

	return_value = -1;
	if (!cmd)
		return (-1);
	if (ft_strcmp(cmd->arg, "cd") == 0)
		return_value = ft_cd(cmd, t_envp);
	if (ft_strcmp(cmd->arg, "echo") == 0)
		return_value = ft_echo(fd, cmd, *t_envp);
	if (ft_strcmp(cmd->arg, "env") == 0)
		return_value = ft_env(fd, t_envp);
	if (ft_strcmp(cmd->arg, "exit") == 0)
		return_value = ft_exit(fd, cmd, t_envp); // Have to do exit
	if (ft_strcmp(cmd->arg, "export") == 0)
		return_value = ft_export(fd, *t_envp, cmd);
	if (ft_strcmp(cmd->arg, "pwd") == 0)
		return_value = ft_pwd(*t_envp);
	if (ft_strcmp(cmd->arg, "unset") == 0)
		return_value = ft_unset(t_envp, cmd);
	return (return_value);
}
