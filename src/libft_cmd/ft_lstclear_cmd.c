/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:26:39 by tchartie          #+#    #+#             */
/*   Updated: 2024/03/28 21:11:06 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstclear_cmd(t_cmd **lst)
{
	t_cmd	*array;

	if (lst)
	{
		while (*lst)
		{
			array = (*lst)->next;
			ft_lstdelone_cmd(*lst);
			(*lst) = array;
		}
	}
}
