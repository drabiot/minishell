/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:43:53 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/15 11:30:42 by tchartie         ###   ########.fr       */
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

static void	delete_path(int type, t_glob **t_envp)
{
	t_glob	*tmp;

	tmp = NULL;
	if (*t_envp)
		tmp = *t_envp;
	if (type == 0)
	{
		while (tmp && ft_strcmp(tmp->name, "PWD") != 0)
			tmp = tmp->next;
		tmp->equal = 10;
	}
	if (type == 1)
	{
		while (tmp && ft_strcmp(tmp->name, "OLDPWD") != 0)
			tmp = tmp->next;
		tmp->equal = 10;
	}
}

int	ft_unset(t_glob **t_envp, t_exec *exec)
{
	int		i;
	char	*word;

	i = 0;
	if (!exec->flags)
		return (1);
	while (exec->flags[i])
	{
		word = exec->flags[i];
		if (word && ft_strcmp(word, "PWD") == 0)
			delete_path(0, t_envp);
		else if (word && ft_strcmp(word, "OLDPWD") == 0)
			delete_path(1, t_envp);
		else if (i != 0)
			delete_glob(t_envp, word);
		i++;
	}
	return (0);
}
