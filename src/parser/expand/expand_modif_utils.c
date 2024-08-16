/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_modif_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:02:25 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/16 16:18:28 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	split_full_no_arg(t_cmd *list)
{
	list->arg = "";
	list->type = NONE;
}

void	split_full(char *full, t_cmd *list)
{
	char	**args;
	int		i;

	args = NULL;
	i = 0;
	if (list)
	{
		free(list->arg);
		list->arg = NULL;
	}
	args = ft_define_split(full);
	if (!args)
		split_full_no_arg(list);
	else
	{
		while (args[i])
		{
			add_new_node(&list, args[i], args[i + 1]);
			list = list->next;
			i++;
		}
	}
	free(args);
}

char	**ft_define_split(char *full)
{
	int		i;
	int		quote;
	char	**split_args;

	i = 0;
	quote = -1;
	while (i < (int)ft_strlen(full))
	{
		if (full[i] == '"' || full[i] == '\'')
			quote = i;
		if (quote != -1 && full[i] == full[quote] && i != quote)
			quote = -1;
		if (quote == -1 && full[i] == ' ')
			full[i] = '\b';
		i++;
	}
	split_args = ft_split(full, '\b');
	return (split_args);
}

void	add_new_node_arg(t_cmd *new_node, char *next_arg)
{
	if (next_arg)
		new_node->arg = ft_strdup(next_arg);//
	new_node->type = WORD;
}

void	add_new_node(t_cmd **list, char *argument, char *next_arg)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		;
	//exit
	add_new_node_arg(new_node, next_arg);
	if (list)
		new_node->index = (*list)->index + 1;
	else
		new_node->index = 0;
	if ((*list)->next)
		new_node->next = (*list)->next;
	else
		new_node->next = NULL;
	if (!list)
		return ;
	if ((*list)->arg)
		free((*list)->arg);
	(*list)->arg = argument;
	if (next_arg)
		(*list)->next = new_node;
	else
		free(new_node);
}
