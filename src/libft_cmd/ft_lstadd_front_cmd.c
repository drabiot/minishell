/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:45:51 by tchartie          #+#    #+#             */
/*   Updated: 2024/03/28 21:11:01 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstadd_front_cmd(t_cmd **lst, t_cmd *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
