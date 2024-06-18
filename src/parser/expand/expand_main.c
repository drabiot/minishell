/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:12:56 by nberduck          #+#    #+#             */
/*   Updated: 2024/06/18 22:33:42 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	ft_have_expand(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] && arg[i + 1] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void ft_expand(t_cmd **list, t_glob *t_envp)
{
	t_cmd	*tmp;
	t_cmd	*t_next;

	tmp = *list;
	t_next = ft_lstnew_cmd(NULL, 0, 0);
	if (!t_next)
		return ;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			if (ft_have_expand(tmp->arg) && !ft_verif_main(tmp->arg))
			{
				t_next->next = tmp->next;
				ft_expand_modif_main(tmp, t_envp);
				tmp = t_next;
			}
			else
				tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	ft_lstclear_cmd(&t_next);
}
