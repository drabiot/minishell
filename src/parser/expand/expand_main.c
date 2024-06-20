/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:12:56 by nberduck          #+#    #+#             */
/*   Updated: 2024/06/20 20:00:54 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	ft_have_expand(char *arg, t_cmd *tmp, t_glob *t_envp)
{
	int	i;

	i = 0;
	(void)t_envp;
	(void)tmp;
	while (arg[i])
	{
		/*if (arg[i] == '$' && arg[i + 1] == '?')
		{
			tmp->arg = ft_itoa(t_envp->utils->return_code);
			return (0);
		}*/
		if (arg[i] == '$' && arg[i + 1] && (arg[i + 1] != ' '
			&& arg[i + 1] != '"' && arg[i + 1] != '\''))
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
			while (ft_have_expand(tmp->arg, tmp, t_envp) && !ft_verif_main(tmp->arg))
			{
				t_next->next = tmp->next;
				ft_expand_modif_main(tmp, t_envp);
			}
			if (!(ft_have_expand(tmp->arg, tmp, t_envp) && !ft_verif_main(tmp->arg)))
				tmp = tmp->next;
			else
				tmp = t_next;
		}
		else
			tmp = tmp->next;
	}
	ft_lstclear_cmd(&t_next);
}
