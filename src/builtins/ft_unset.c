/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:43:53 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/18 23:21:30 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	delete_glob(t_glob **t_envp, char *del_arg)
{
	t_glob	*tmp;
	t_glob	*next_node;

	tmp = NULL;
	next_node = NULL;
	if (*t_envp)
		tmp = *t_envp;
	if (!del_arg)
		return ;
	while (tmp->next && ft_strcmp(tmp->next->name, del_arg) != 0)
		tmp = tmp->next;
	if (!tmp->next)
		return ;
	next_node = tmp->next->next;
	if (ft_strcmp(tmp->next->name, del_arg) == 0)
		ft_lstdelone_glob(tmp->next);
	tmp->next = next_node;
}

int	ft_unset(t_glob **t_envp, t_exec *exec)
{
	int		i;
	char	*last_word;

	i = 0;
	if (!exec->flags)
		return (1);
	while (exec->flags[i + 1])
		i++;
	last_word = exec->flags[i];
	if (i != 0)
		delete_glob(t_envp, last_word);
	return (0);
}
