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

int	ft_echo(int fd, t_cmd *cmd, t_glob *t_envp)
{
	int		option;
	t_cmd	*tmp;

	option = 0;
	t_envp->utils->return_code = 0;
	if (!cmd->next)
	{
		ft_putstr_fd("\n", fd);
		return (1);
	}
	if (ft_strcmp(cmd->next->arg, "-n") == 0)
		option = 1;
	if (option == 1)
		tmp = cmd->next->next;
	else
		tmp = cmd->next;
	while (tmp)
	{
		ft_putstr_fd(tmp->arg, fd);
		if (tmp->next)
			ft_putstr_fd(" ", fd);
		tmp = tmp->next;
	}
	if (option == 0)
		ft_putstr_fd("\n", fd);
	return (0);
}
