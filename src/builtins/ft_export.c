/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:19:50 by nberduck          #+#    #+#             */
/*   Updated: 2024/05/26 19:37:21 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_verif_args(t_cmd *args)
{
	unsigned int	i;
	
	while (args)
	{
		i = 0;
		while (args->arg[i] && args->arg[i] != '=' )
		{
			if(!ft_isalpha(args->arg[i]) && !ft_isdigit(args->arg[i]))
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
static void	ft_env_print(t_glob *t_envp)
{
	t_glob			*tmp;
	unsigned int	i;
	int				name_end;
	

	tmp = t_envp;
	while (tmp)
	{
		i = 0;
		name_end = 0;
		if (tmp->equal)
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->content);
		else
			printf("declare -x %s\n", tmp->name);
		tmp = tmp->next;
   }
}

int	ft_export(t_glob **t_envp, t_cmd *args)
{
	t_cmd	*curr;
	t_glob	*tmp;
	// printf("%p.\n", args);
	while (args)
	{
		if (!args || !args->arg)
		{
			ft_env_print(*t_envp);
			return(0);
		}
		printf("%s.\n", args->arg);
		ft_expand(&args, *t_envp);
		if (!ft_verif_args(args))
		{
			if (ft_check_quote_and_delete(&args))
				return (1);
			curr = args;
			while (curr)
			{
				tmp = ft_globsolo_creation(args->arg);
				printf("%s\n", tmp->name);
				ft_lstadd_back_alpha_envp(t_envp, tmp);
			curr = curr->next;
			}
		}
		else
			return (1);
		args = args->next;
	}
	return (0);
}
