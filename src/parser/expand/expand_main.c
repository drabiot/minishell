/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:12:56 by adorlac           #+#    #+#             */
/*   Updated: 2024/07/05 12:02:16 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	ft_have_expand(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	ft_expand(t_cmd **list, t_list *t_envp)
{
	t_cmd	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			if (ft_have_expand(tmp->arg) && !ft_verif_main(tmp->arg))
				ft_expand_modif_main(tmp, t_envp);
		}
		tmp = tmp->next;
	}
}
