/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:36:16 by nberduck          #+#    #+#             */
/*   Updated: 2024/06/01 17:27:27 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_start_execution(int fd, t_glob **t_envp, t_cmd *cmd)
{
	int		return_value;
	t_cmd	*start;
	
	printf("%i\n", cmd->type);
	if (cmd->type == COMMAND)
	{
		start = ft_lstnmap_cmd(cmd);
		return_value = ft_find_builtins_part1(fd, t_envp, start);
		if (return_value == -1)
			return_value = ft_execute_other_cmd(fd, t_envp, start);
		return (return_value);
	}
	return (0);
}

int	ft_execution_main(t_glob **t_envp, t_cmd *cmd)
{
	// printf("%s\n", "t");
	if (ft_pipe_len(cmd) != 1)
		return (0); // Need to create child here etc...
	else
		return (ft_start_execution(1, t_envp, cmd));
	
	return (0);
}