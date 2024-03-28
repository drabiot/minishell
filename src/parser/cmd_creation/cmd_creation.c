/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:40:08 by nberduck          #+#    #+#             */
/*   Updated: 2024/03/28 21:30:16 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_cmd	*ft_cmd_creation(char *arg, int index)
{
	t_cmd	*tmp;
	int		type;
	
	type = ft_find_type(arg);
	tmp = ft_lstnew_cmd(arg, type, index);
	return (tmp);
}