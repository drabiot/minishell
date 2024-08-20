/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 23:14:04 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/20 23:27:52 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	swap_data(t_glob **i, t_glob **j)
{
	t_glob	*tmp;

	tmp = &(t_glob){0};
	tmp->name = (*i)->name;
	tmp->equal = (*i)->equal;
	tmp->content = (*i)->content;
	(*i)->name = (*j)->name;
	(*i)->equal = (*j)->equal;
	(*i)->content = (*j)->content;
	(*j)->name = tmp->name;
	(*j)->equal = tmp->equal;
	(*j)->content = tmp->content;
}

t_glob	*sort_env(t_glob *glob)
{
	t_glob	*i;
	t_glob	*j;

	i = NULL;
	j = NULL;
	if (!glob)
		return (NULL);
	i = glob->next;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strncmp(i->name, j->name, ft_strlen(i->name)) > 0)
				swap_data(&i, &j);
			j = j->next;
		}
		i = i->next;
	}
	return (glob);
}
