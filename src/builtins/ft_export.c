/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:19:50 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/30 00:53:19 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_verif_args(char *flag, t_glob *t_envp, t_bool error)
{
	unsigned int	i;

	if (!flag && !error)
	{
		t_envp->utils->return_code = 0;
		return (0);
	}
	if (flag[0] == '=')
	{
		t_envp->utils->return_code = 1;
		ft_putstr_fd(" not a valid identifier\n", 2);
		return (1);
	}
	i = 0;
	while (flag[i] && flag[i] != '=' )
	{
		if (!ft_isalpha(flag[i]))
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

int	ft_export(int fd, t_glob *t_envp, t_exec *exec)
{
	t_glob	*tmp;
	int		i;
	t_bool	error;

	i = 1;
	error = FALSE;
	if (!exec->flags[1])
	{
		ft_env_print(fd, t_envp);
		return (0);
	}
	//ft_expand(&args, t_envp);
	while (exec->flags[i])
	{
		if (!ft_verif_args(exec->flags[i], t_envp, error))
		{
			if (ft_check_quote_and_delete(&exec))
				return (0);
			tmp = ft_globsolo_creation(exec->flags[i]);
			ft_lstadd_back_alpha_envp(&t_envp, tmp);
		}
		else
			error = TRUE;
		i++;
	}
	return (error);
}
