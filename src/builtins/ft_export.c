/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:19:50 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/07 16:52:35 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_verif_args(char *flag, t_glob *t_envp, t_bool error)
{
	unsigned int	i;

	i = 0;
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
	while (flag[i] && flag[i] != '=' )
	{
		if (!ft_isalpha(flag[i]))
		{
			if (flag[i] == '+' && flag[i + 1] == '=')
				return (-1);
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
		if (tmp->equal == 1)
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(tmp->name, fd);
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(tmp->content, fd);
			ft_putstr_fd("\"\n", fd);
		}
		else if (tmp->equal == 0)
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(tmp->name, fd);
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd("\n", fd);
		}
		tmp = tmp->next;
	}
}

t_bool	no_glob(t_glob **t_envp, char *glob)
{
	char	*name;
	int		i;
	t_glob	*list;

	name = NULL;
	i = 0;
	if (*t_envp)
		list = *t_envp;
	while (glob[i] && glob[i] != '=' && glob[i] != '+')
		i++;
	name = ft_substr(glob, 0, i);
	while (list)
	{
		if (ft_strcmp(name, list->name) == 0)
		{
			free(name);
			return (FALSE);
		}
		list = list->next;
	}
	free(name);
	return (TRUE);
}

void	change_glob(t_glob **t_envp, char *glob, int type)
{
	char	*name;
	char	*content;
	int		i;
	int		start_content;
	t_glob	*list;

	name = NULL;
	i = 0;
	if (*t_envp)
		list = *t_envp;
	while (glob[i] && glob[i] != '=' && glob[i] != '+')
		i++;
	name = ft_substr(glob, 0, i);
	start_content = i;
	if (glob[start_content] == '+' && glob[start_content + 1] == '=')
		start_content++;
	if (glob[start_content == '='])
		start_content++;
	i = start_content;
	while (glob && glob[i])
		i++;
	content = ft_substr(glob, start_content, i - start_content);
	if (type == 0)
	{
		while (list && ft_strcmp(name, list->name) != 0)
			list = list->next;
		list->content = content;
	}
	else if (type == 1)
	{
		while (list && ft_strcmp(name, list->name) != 0)
			list = list->next;
		list->content = ft_strjoin(list->content, content);
		free(content);
	}
	free(name);
}

int	ft_export(int fd, t_glob *t_envp, t_exec *exec)
{
	t_glob	*tmp;
	int		i;
	t_bool	error;
	int		state;

	i = 1;
	error = FALSE;
	state = 0;
	if (!exec->flags[1])
	{
		ft_env_print(fd, t_envp);
		return (0);
	}
	//ft_expand(&args, t_envp);
	while (exec->flags[i])
	{
		state = ft_verif_args(exec->flags[i], t_envp, error);
		if (state < 1)
		{
			if (state == 0)
			{
				if (ft_check_quote_and_delete(&exec))
					return (0);
				if (no_glob(&t_envp, exec->flags[i]))
				{
					tmp = ft_globsolo_creation(exec->flags[i]);
					ft_lstadd_back_alpha_envp(&t_envp, tmp);
				}
				else
					change_glob(&t_envp, exec->flags[i], 0);
			}
			else if (state == -1)
			{
				if (ft_check_quote_and_delete(&exec))
					return (0);
				if (no_glob(&t_envp, exec->flags[i]))
				{
					tmp = ft_globsolo_creation(exec->flags[i]);
					ft_lstadd_back_alpha_envp(&t_envp, tmp);
				}
				else
					change_glob(&t_envp, exec->flags[i], 1);
			}
		}
		else
			error = TRUE;
		i++;
	}
	return (error);
}

