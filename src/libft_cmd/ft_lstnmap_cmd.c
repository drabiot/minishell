/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnmap_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 01:06:41 by nberduck          #+#    #+#             */
/*   Updated: 2024/06/09 01:09:37 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*ft_lstnmap_cmd(t_cmd *cmd, int npipe)
{
	t_cmd	*start;
	t_cmd	*buff;
	t_cmd	*tmp;
	int		tmp_len;
	int		npipe_tmp;
	
	npipe_tmp = 1;
	while (npipe_tmp != npipe)
	{
		npipe_tmp++;
		cmd = cmd->next;
	}
	start = ft_lstnew_cmd(cmd->arg, cmd->type, 0);
	if (!cmd->next)
		return (start);
	tmp_len = 1;
	tmp = cmd->next;
	while (tmp && tmp->type != PIPE)
	{
		buff = ft_lstnew_cmd(tmp->arg, tmp->type, tmp_len);
		ft_lstadd_back_cmd(&start, buff);
		tmp = tmp->next;
		tmp_len++;
	}
	return (start);
}
