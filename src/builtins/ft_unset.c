/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:43:53 by nberduck          #+#    #+#             */
/*   Updated: 2024/03/19 17:31:42 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void ft_tmp_free(char **tmp)
{
	unsigned int	i;
	
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

static t_list *split_args(char **args)
{
	unsigned int	i;
	unsigned int	j;
	char			**tmp;
	t_list			*arg;

	i = 0;
	j = 0;
	arg = NULL;
	while (args[i])
	{
		tmp = ft_split(args[i], ' ');
		j = 0;
		while (tmp[j])
		{
			ft_lstadd_back(&arg, ft_lstnew(ft_strdup(tmp[j])));
			j++;
		}
		ft_tmp_free(tmp);
		tmp = NULL;
		i++;
	}
	return (arg);
}
static ft_find_arg(t_list **t_envp, char **arg)
{
	t_list *tmp;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (arg)
	{
		while (tmp)
		{
			j = 0;
			while ((str *)tmp->content[j] == arg[j])
				j++;
			if ((str *)tmp->content[j] == '=')
			{
				//Need to delete node here
				tmp = NULL;
			}
			tmp = tmp->next;
		}
		i++;
	}
}

int	ft_unset(t_list **t_envp, char **args)
{
	t_list *arg;
	
	//Need to find better name for arg and args
	arg = split_args(args);
	if (!arg)
		return (1);

	ft_find_arg(t_envp, arg);
	
	t_list *tmp;
	tmp = arg;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&arg, free);
	return (0);
}