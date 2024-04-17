/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:19:50 by nberduck          #+#    #+#             */
/*   Updated: 2024/04/17 11:52:08 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_verif_args(t_cmd *args)
{
	unsigned int	i;
	
	while (args)
	{
		if (ft_isdigit(args->arg[0]))
		{
			printf("texport: '%s': not a valid identifier\n", args->arg);
			return (1);
		}
		i = 0;
		while (args->arg[i] != '=')
		{
			if(!ft_isalpha(args->arg[i]) && args->arg[i] != '_')
			{
				printf("export: '%s': not a valid identifier\n", args->arg);
				return (1);
			}
			i++;
		}
		args = args->next;
	}
	return (0);
}
static void	ft_env_print(t_list *t_envp)
{
	t_list			*tmp;
	unsigned int	i;
	int				name_end;
	char			*content;
	

	tmp = t_envp;
	while (tmp)
	{
		content = (char *)tmp->content;
		i = 0;
		name_end = 0;
		printf("declare -x ");
		while (content[i] && name_end != -1)
		{
			if (content[i] == '=')
				name_end = -1;
			printf("%c", content[i]);
			i++;
		}
		printf("\"%s\"\n", &content[i + 1]);
		tmp = tmp->next;
   }
}

int	ft_export(t_list **t_envp, t_cmd **args)
{
	t_cmd	*curr;
	t_list	*tmp;
	if (!args)
		ft_env_print(*t_envp);
	if (!ft_verif_args(*args))
	{
		if (ft_check_quote_and_delete(args))
			return (1);
		ft_expand(args, *t_envp);
		curr = *args;
		while (curr)
		{
			tmp = ft_lstnew(ft_strdup(curr->arg));
			ft_lstadd_back(t_envp, tmp);
		curr = curr->next;
		}
	}
	else
		return (1);
	return (0);
}
