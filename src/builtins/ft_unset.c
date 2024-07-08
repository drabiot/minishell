/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:43:53 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/05 12:50:24 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_delete_arg(t_list **t_envp, unsigned int place)
{
	unsigned int	i;
	t_list			*tmp;
	t_list			*next_after_clear;
	char			*tmp_content;

	i = 0;
	tmp = *t_envp;
	while (i < place - 1)
	{
		tmp_content = (char *)tmp->content;
		printf("%s\n", tmp_content);
		tmp = tmp->next;
		i++;
	}
	next_after_clear = tmp->next->next;
	ft_lstdelone(tmp->next, free);
	tmp->next = next_after_clear;
}

static void	ft_find_arg(t_list **t_envp, t_list *arg)
{
	t_list			*tmp;
	unsigned int	i;
	int				place;
	char			*tmp_content;
	char			*arg_content;

	place = 0;
	arg_content = (char *)arg->content;
	tmp = *t_envp;
	while (tmp)
	{
		tmp_content = (char *)tmp->content;
		i = 0;
		while (tmp_content[i] == arg_content[i])
			i++;
		if (tmp_content[i] == '=')
		{
			ft_delete_arg(t_envp, place);
			tmp = NULL;
		}
		else
			tmp = tmp->next;
		place++;
	}
}

int	ft_unset(t_list **t_envp, char **args)
{
	t_list	*t_args;
	t_list	*tmp;

	t_args = split_args(args);
	if (!t_args)
		return (1);
	tmp = t_args;
	while (tmp)
	{
		ft_find_arg(t_envp, tmp);
		tmp = tmp->next;
	}
	ft_lstclear(&t_args, free);
	return (0);
}
