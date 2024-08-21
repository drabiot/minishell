/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcreate_glob.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 05:34:01 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/21 20:50:13 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_name_len(char *tmp)
{
	int	i;

	if (!tmp)
		return (0);
	i = 0;
	while (tmp[i] != '=' && tmp[i])
		i++;
	return (i);
}

static t_bool	is_not_equal(t_glob *tmp, t_glob *new)
{
	if (ft_strcmp(tmp->name, new->name) == 0)
	{
		if (new->equal == 0)
		{
			ft_lstdelone_glob(new);
			return (FALSE);
		}
		free(tmp->content);
		tmp->content = ft_strdup(new->content);
		tmp->equal = 1;
		ft_lstdelone_glob(new);
		return (FALSE);
	}
	return (TRUE);
}

void	ft_lstadd_back_alpha_envp(t_glob **list, t_glob *new)
{
	t_glob	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
	{
		if (!is_not_equal(tmp, new))
			return ;
		tmp = tmp->next;
	}
	if (new->equal != 10)
		ft_lstadd_back_glob(list, new);
}

static void	fill_node_glob(char **env, t_glob *list, int i)
{
	int				name_end;
	char			*name;
	char			*content;
	t_glob			*tmp;

	name_end = ft_name_len(env[i]);
	name = ft_substr(env[i], 0, name_end);
	content = ft_substr(env[i], name_end + 1, ft_strlen(env[i]));
	if (name[0] == '_' && ft_strlen(name) == 1)
		tmp = ft_lstnew_glob(ft_strdup(name), 20, ft_strdup(content));
	else if (env[i][name_end] && env[i][name_end] == '=')
		tmp = ft_lstnew_glob(ft_strdup(name), 1, ft_strdup(content));
	else
		tmp = ft_lstnew_glob(ft_strdup(name), 0, ft_strdup(content));
	ft_lstadd_back_alpha_envp(&list, tmp);
	if (name)
	{
		free (name);
		name = NULL;
	}
	if (content)
	{
		free (content);
		content = NULL;
	}
}

t_glob	*ft_envp_creation(char **env)
{
	t_glob			*list;
	t_glob			*tmp;
	unsigned int	i;

	i = 0 ;
	list = NULL;
	tmp = ft_lstnew_glob("", 10, "");
	ft_lstadd_back_alpha_envp(&list, tmp);
	while (env[i])
	{
		fill_node_glob(env, list, i);
		i++;
	}
	return (list);
}
