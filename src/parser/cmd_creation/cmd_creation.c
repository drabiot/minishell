/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:40:08 by adorlac           #+#    #+#             */
/*   Updated: 2024/07/05 12:39:15 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_cmd	*ft_cmd_creation(char *arg, int index, t_cmd *linked_list)
{
	t_cmd	*tmp;
	int		type;
	t_cmd	*prev;
	int		i;

	i = 1;
	prev = NULL;
	while (i < index)
	{
		linked_list = linked_list->next;
		i++;
	}
	if (index >= 1)
		prev = linked_list;
	type = ft_find_type(arg, prev);
	tmp = ft_lstnew_cmd(arg, type, index);
	return (tmp);
}
