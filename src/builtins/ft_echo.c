/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:22:53 by tchartie         #+#    #+#             */
/*   Updated: 2024/06/26 07:31:48 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	null_echo(t_exec *exec, int fd)
{
	if (!exec->flags[1])
	{
		ft_putstr_fd("\n", fd);
		return (1);
	}
	return (0);
}

static void	exec_echo(t_exec *exec, int pos_flag, int fd)
{
	int	i;

	i = pos_flag;
	while (exec->flags[i])
	{
		ft_putstr_fd(exec->flags[i], fd);
		if (exec->flags[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (pos_flag == 1)
		ft_putstr_fd("\n", fd);
}

int	ft_echo(int fd, t_exec *exec, t_glob *t_envp)
{
	int		option;

	t_envp->utils->return_code = 0;
	option = 1;
	if (null_echo(exec, fd))
		return (0);
	if (ft_strcmp(exec->flags[1], "-n") == 0)
		option = 2;
	exec_echo(exec, option, fd);
	return (0);
}
