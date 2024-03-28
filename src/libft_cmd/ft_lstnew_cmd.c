/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:41:40 by tchartie          #+#    #+#             */
/*   Updated: 2024/03/28 21:11:53 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*ft_lstnew_cmd(char *arg, int type, int index)
{
	t_cmd	*array;

	array = (t_cmd *)malloc(sizeof(t_cmd));
	if (!array)
		return (NULL);
	array->next = NULL;
	array->arg = arg;
    array->type = type;
    array->index = index;
	return (array);
}
