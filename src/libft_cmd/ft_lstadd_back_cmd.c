/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:51:40 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/09 14:50:05 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*array;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			array = ft_lstlast_cmd(*(lst));
			array->next = new;
		}
	}
}
