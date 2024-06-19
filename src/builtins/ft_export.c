/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:19:50 by nberduck          #+#    #+#             */
/*   Updated: 2024/06/19 19:59:00 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_verif_args(int fd, t_cmd *args)
{
	unsigned int	i;
	(void)fd;
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
static void	ft_env_print(int fd, t_glob *t_envp)
{
	t_glob			*tmp;
	unsigned int	i;
	int				name_end;
	
	(void)fd;
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
//Have to do with fd
int	ft_export(int fd, t_glob **t_envp, t_cmd *args)
{
	t_cmd	*curr;
	t_glob	*tmp;
	while (args)
	{
		if (!args || !args->arg)
		{
			ft_env_print(fd, *t_envp);
			return(0);
		}
		ft_expand(&args, *t_envp);
		if (!ft_verif_args(fd, args))
		{
			if (ft_check_quote_and_delete(&args))
				return (1);
			curr = args;
			while (curr)
			{
				tmp = ft_globsolo_creation(args->arg);
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
