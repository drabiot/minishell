/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_glob.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:51:40 by tchartie          #+#    #+#             */
/*   Updated: 2024/06/25 23:22:54 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstadd_back_glob(t_glob **lst, t_glob *new)
{
	t_glob	*array;
	
	// printf("name: %s, equal: %d, content: %s\n", new->name, new->equal, new->content);
	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			array = ft_lstlast_glob(*(lst));
			// printf("name: %s\n", array->name);
			array->next = new;
		}
	}
	// while (*lst)
	// {
	// 	printf("name: %s\n", (*lst)->name);
	// 	*lst = (*lst)->next;
	// }
}
