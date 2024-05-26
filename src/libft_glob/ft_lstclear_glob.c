/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_glob.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:26:39 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/23 10:24:50 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstclear_glob(t_glob **lst)
{
	t_glob	*array;

	if (lst)
	{
		while (*lst)
		{
			array = (*lst)->next;
			ft_lstdelone_glob(*lst);
			(*lst) = array;
		}
	}
}
