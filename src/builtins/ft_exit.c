/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:48:41 by nberduck          #+#    #+#             */
/*   Updated: 2024/06/20 20:57:15 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int ft_get_alpha(char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if (ft_isalpha(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(int fd, t_cmd *cmd, t_glob **t_envp)
{
	int	exit;

	if ((cmd->next && cmd->next->next ))
	{
		(*t_envp)->utils->return_code = 1;
		ft_putstr_fd(" too many arguments", 2);
		return (1);
	}
	if (ft_get_alpha(cmd->next->arg))
	{
		(*t_envp)->utils->return_code = 2;
		ft_putstr_fd(" numeric argument required", 2);
		return (2);
	}
	exit = ft_atoi(cmd->next->arg);
	if (exit > 256)
		exit %= 256; 
	if (exit < 0)
		exit = 256 - (-exit) % 256;
	(*t_envp)->utils->return_code = exit;
	ft_putstr_fd("exit\n", fd);
	return (exit);
}