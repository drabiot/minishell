/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:43:53 by tchartie          #+#    #+#             */
/*   Updated: 2024/06/26 07:13:50 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void ft_delete_arg(t_glob **t_envp, unsigned int place)
{
	unsigned int	i;
	t_glob			*tmp;
	t_glob			*next_after_clear;

	i = 0;
	tmp = *t_envp;
	while (i < place - 1)
	{
		tmp = tmp->next;
		i++;
	}
	next_after_clear = tmp->next->next;
	ft_lstdelone_glob(tmp->next);
	tmp->next = next_after_clear;
}

static void ft_find_arg(t_glob **t_envp, t_cmd *arg)
{
	t_glob *tmp;
	unsigned int	place;

	place = 0;
	tmp = *t_envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, arg->arg) == 0)
		{
			ft_delete_arg(t_envp, place);
			tmp = NULL;
		}
		else
			tmp = tmp->next;
		place++;
	}
}

int	ft_unset(t_glob **t_envp, t_cmd *args)
{
	t_cmd	*tmp;
	
	if (!args)
		return (1);
	tmp = args;
	while (tmp)
	{
		ft_find_arg(t_envp, tmp);
		tmp = tmp->next;
	}
	(*t_envp)->utils->return_code = 0;
	return (0);
}
