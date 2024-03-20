/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:43:53 by nberduck          #+#    #+#             */
/*   Updated: 2024/03/20 16:30:16 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void ft_delete_arg(t_list **t_envp, unsigned int len, t_list **tmp_main)
{
	unsigned int	i;
	t_list			*tmp;
	t_list			*next;

	tmp = *t_envp;
	i = 0;
	while (i < len - 1)
	{
		tmp = tmp->next;
		i++;
	}
	next = tmp->next->next;
	ft_lstdelone(tmp->next, free);
	tmp->next = next;
	*tmp_main = NULL;
}
static void ft_find_arg(t_list **t_envp, t_list *arg)
{
	t_list			*tmp;
	unsigned int	i;
	unsigned int	place;
	char			*content_tmp;
	char			*content_arg;

	while (arg)
	{
		place = 0;
		tmp = *t_envp;
		while (tmp)
		{
			i = 0;
			content_arg = (char *)arg->content;
			content_tmp = (char *)tmp->content;
			while (content_tmp[i] == content_arg[i])
				i++;
			if (content_tmp[i] == '=')
				ft_delete_arg(t_envp, place, &tmp);
			else
				tmp = tmp->next;
			place++;
		}
		arg = arg->next;
	}
}

int	ft_unset(t_list **t_envp, char **args)
{
	t_list *t_args;
	t_list *tmp;

	t_args = split_args(args);
	if (!t_args)
		return (1);
	ft_find_arg(t_envp, t_args);
	tmp = t_args;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&t_args, free);
	return (0);
}
