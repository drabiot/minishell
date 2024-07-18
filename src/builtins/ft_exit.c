/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:48:41 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/18 22:26:39 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_get_alpha(char *arg)
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

int	ft_exit(int fd, t_exec *exec, t_glob **t_envp)
{
	int	exit;

	exit = (*t_envp)->utils->return_code;
	if (exec->flags[2])
	{
		(*t_envp)->utils->return_code = 1;
		ft_putstr_fd(" too many arguments", 2);
		return (1);
	}
	if (exec->flags[1] && ft_get_alpha(exec->flags[1]))
	{
		(*t_envp)->utils->return_code = 2;
		ft_putstr_fd(" numeric argument required", 2);
		return (2);
	}
	if (exec->flags[1])
		exit = ft_atoi(exec->flags[1]);
	if (exit >= 256)
		exit %= 256;
	if (exit < 0)
		exit = 256 - (-exit) % 256;
	(*t_envp)->utils->return_code = exit;
	ft_putstr_fd("exit\n", fd);
	return (exit);
}
