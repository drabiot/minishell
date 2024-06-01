/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:22:53 by nberduck          #+#    #+#             */
/*   Updated: 2024/05/30 05:19:52 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo(int fd, t_cmd *cmd)
{
	int		option;
	t_cmd	*tmp;

	option = 0;
	if (!cmd)
		return (1);
	if (ft_strcmp(cmd->next->arg, "-n") == 0)
		option = 1;
	if (option == 1)
		tmp = cmd->next->next;
	else
		tmp = cmd->next;
	while (tmp)
	{
		ft_putstr_fd(tmp->arg, fd);
		tmp = tmp->next;
	}
	//For option -n
	if (option == 0)
		ft_putstr_fd("\n", fd);
	return (0);
}
