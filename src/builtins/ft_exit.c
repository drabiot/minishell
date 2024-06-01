/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:48:41 by nberduck          #+#    #+#             */
/*   Updated: 2024/05/30 05:23:16 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(int	fd, t_cmd *cmd)
{
	(void)fd;
	int	exit;

	exit = ft_atoi(cmd->arg);
	//Have to do the real exit lmao
	printf("%i\n", exit);
	if (exit != 0)
		return (1);
	return (0);
}