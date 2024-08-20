/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:40:22 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/20 15:40:59 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_exec	*ft_last_node(t_exec *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_back(t_exec **lst, t_exec *new)
{
	t_exec *buffer;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		buffer = ft_last_node((*lst));
		buffer->next = new;
	}
}

void	check_node(t_cmd *cmd, t_glob *t_envp, t_exec *list, t_exec *nd)
{
	if ((!nd->flags || !nd->cmd) && nd->base_cmd)
	{
		free_t_cmd(cmd);
		free_exit(list, t_envp);
		exit (0);
	}
}