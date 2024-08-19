/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:19:50 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/19 18:52:48 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_verif_arg(char *flg, t_glob *t_envp, t_bool err, unsigned int i)
{
	int	r;

	r = ft_verif_arg_start(flg, err, t_envp);
	if (r == 0 || r == 1)
		return (r);
	while (flg[i] && flg[i] != '=')
	{
		if (!ft_isalpha(flg[i]))
		{
			if (flg[i] == '+' && flg[i + 1] == '=' )
				return (-2);
			t_envp->utils->return_code = 1;
			ft_putstr_fd(" not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	if (flg[i] == '=')
		return (-1);
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
			ft_env_print_one(fd, tmp);
		else if (tmp->equal == 0)
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(tmp->name, fd);
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

void	change_glob(t_glob **t_envp, char *glob, int type, int i)
{
	char	*name;
	char	*content;
	int		start_content;
	char	*tmp_content;
	t_glob	*list;

	name = NULL;
	tmp_content = NULL;
	if (*t_envp)
		list = *t_envp;
	while (glob[i] && glob[i] != '=' && glob[i] != '+')
		i++;
	name = ft_substr(glob, 0, i);
	start_content = i;
	start_content = change_glob_sign(glob, start_content);
	i = start_content;
	while (i < (int)ft_strlen(glob))
		i++;
	content = ft_substr(glob, start_content, i - start_content);
	if (type == -1)
		change_glob_one(list, name, content);
	else if (type == -2)
		change_glob_two(list, name, content, tmp_content);
	free(name);
}

int	ft_export(int fd, t_glob *t_envp, t_exec *exec)
{
	int	i;
	int	error;
	int	state;
	int	flg;

	i = 1;
	flg = 0;
	error = FALSE;
	if (!exec->flags[1])
	{
		ft_env_print(fd, t_envp);
		return (0);
	}
	while (exec->flags[i])
	{
		state = ft_verif_arg(exec->flags[i], t_envp, error, 0);
		flg = handle_state(&t_envp, exec, state, i);
		if (flg > 0)
			error = TRUE;
		i++;
	}
	return (error);
}
