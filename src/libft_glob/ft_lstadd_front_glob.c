/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_glob.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:45:51 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/23 10:01:49 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstadd_front_glob(t_glob **lst, t_glob *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
