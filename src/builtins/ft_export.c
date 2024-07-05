/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:19:50 by nberduck          #+#    #+#             */
/*   Updated: 2024/06/26 07:12:41 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_verif_args(int fd, t_cmd *args, t_glob *t_envp)
{
	unsigned int	i;
	(void)fd;

	if (!args)
	{
		t_envp->utils->return_code = 0;
		return (1);
	}
	if (args->arg[0] && args->arg[0] == '=')
	{
		t_envp->utils->return_code = 1;
		ft_putstr_fd(" not a valid identifier\n", 2);
		return (1);
	}
	i = 0;
	while (args->arg[i] && args->arg[i] != '=' )
	{
		if(!ft_isalpha(args->arg[i]))
		{
			t_envp->utils->return_code = 1;
			ft_putstr_fd(" not a valid identifier\n", 2);
			return (1);
		}
		i++;
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
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(tmp->name, fd);
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(tmp->content, fd);
			ft_putstr_fd("\"\n", fd);
		}
		else
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(tmp->name, fd);
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd("\n", fd);
		}
		tmp = tmp->next;
   }
}

int	ft_export(int fd, t_glob *t_envp, t_cmd *args)
{
	t_cmd	*curr;
	t_glob	*tmp;
	if (!args->next)
	{
		ft_env_print(fd, t_envp);
		return(0);
	}
	while (args)
	{
		ft_expand(&args, t_envp);
		if (!ft_verif_args(fd, args->next, t_envp))
		{
			if (ft_check_quote_and_delete(&args))
				return (1);
			curr = args;
			while (curr)
			{
				tmp = ft_globsolo_creation(curr->arg);
				// printf("name: %s, equal: %d, content: %s\n", tmp->name, tmp->equal, tmp->content);
				ft_lstadd_back_alpha_envp(&t_envp, tmp);
				t_envp->utils->return_code = 0;
				curr = curr->next;
			}
		}
		else
		{
			return (1);
		}
		args = args->next;
	}
	return (0);
}
