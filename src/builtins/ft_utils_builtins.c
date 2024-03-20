/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:22:23 by nberduck          #+#    #+#             */
/*   Updated: 2024/03/20 16:29:49 by nberduck         ###   ########.fr       */
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

t_list *split_args(char **args)
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