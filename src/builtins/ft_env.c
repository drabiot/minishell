/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:30:20 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/19 22:54:07 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*create_current(t_glob *start)
{
	char	*tmp;
	char	*current;

	tmp = NULL;
	current = NULL;
	if (start->equal == 1)
	{
		tmp = ft_strjoin(start->name, "=");
		if (start->content)
			current = ft_strjoin(tmp, start->content);
		if (tmp)
			free(tmp);
	}
	return (current);
}

void	create_env(t_glob **t_envp)
{
	t_glob	*start;
	char	**new_env;
	int		i;
	char	*current;

	i = 0;
	new_env = NULL;
	if (*t_envp)
		start = *t_envp;
	new_env = ft_calloc(ft_lstsize_glob(*t_envp) + 1, sizeof(char *));
	if (!new_env)
		return ;
	while (start)
	{
		current = create_current(start);
		if (current)
		{
			new_env[i] = current;
			i++;
			current = NULL;
		}
		start = start->next;
	}
	(*t_envp)->utils->env = new_env;
}

int	ft_env(int fd, t_glob **t_envp)
{
	t_glob			*tmp;
	char			*first_part;
	char			*last_part;

	if (!*t_envp)
		return (1);
	tmp = *t_envp;
	while (tmp)
	{
		if (tmp->equal == 1)
		{
			first_part = ft_strjoin(tmp->name, "=");
			last_part = ft_strjoin(first_part, tmp->content);
			ft_putstr_fd(last_part, fd);
			ft_putstr_fd("\n", fd);
			free(first_part);
			free(last_part);
		}
		tmp = tmp->next;
	}
	return (0);
}
