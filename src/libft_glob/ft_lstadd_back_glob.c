/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_glob.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:51:40 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/23 10:19:15 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstadd_back_glob(t_glob **lst, t_glob *new)
{
	t_glob	*array;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			array = ft_lstlast_glob(*(lst));
			array->next = new;
		}
	}
}
