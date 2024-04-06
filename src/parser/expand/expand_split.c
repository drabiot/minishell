/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:06:33 by nberduck          #+#    #+#             */
/*   Updated: 2024/04/06 18:30:59 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	expand_split(t_cmd *list, t_cmd *before, char *content)
{
	t_input	cmd;
	t_cmd	*tokenized_content;
	t_cmd	*tmp;

	cmd = (t_input){0};
	cmd.str = content;
	cmd.i = 0;
	tokenized_content = expand_tokenizer(&cmd);
	tmp = tokenized_content;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = before->next;
	while (list->next != before)
		list = list->next;
	list->next = tmp;
	ft_lstdelone_cmd(before);
}
