/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_modif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:50:01 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/07 16:27:02 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*ft_getenv(char *name, t_glob *t_envp, int i)
{
	t_glob	*tmp;
	char	*name_tmp;

	tmp = t_envp;
	while (tmp)
	{
		i = 0;
		name_tmp = (char *)tmp->name;
		if (!ft_strcmp(name_tmp, name))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	add_new_node(t_cmd **list, char *argument, char *next_arg)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		;
		//exit
	new_node->arg = next_arg;
	new_node->type = WORD;
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
	(*list)->arg = argument;
	if (next_arg)
		(*list)->next = new_node;
}

static char	**ft_define_split(char *full)
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
	return(split_args);
}

static void	split_full(char *full, t_cmd *list)
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
	{
		list->arg = "";
		list->type = NONE;
	}
	else
	{
		while (args[i])
		{
			add_new_node(&list, args[i], args[i + 1]);
			list = list->next;
			i++;
		}
	}
}

static void	ft_expand_do(t_cmd *list, char *content, int start, int end)
{
	char	*first_part;
	char	*end_part;
	char	*with_content;
	char	*full;

	with_content = NULL;
	if (start >= 1)
		first_part = ft_substr(list->arg, 0, start - 1);
	else
		first_part = NULL;
	end_part = ft_substr(list->arg, end + 1, ft_strlen(list->arg) - end);
	if (!content)
		full = ft_strjoin(first_part, end_part);
	else
	{
		with_content = ft_strjoin(first_part, content);
		full = ft_strjoin(with_content, end_part);
	}
	//free(list->arg);
	split_full(full, list);
	//list->arg = full;
	if (first_part)
		free(first_part);
	if (end_part)
		free(end_part);
	if (content)
		free(content);
	if (with_content)
		free(with_content);
}

void	ft_expand_modif(t_cmd *cmd, t_glob *t_envp, int type)
{
	int		i;
	int		start;
	int		end;
	char	*content;
	char	*name;
	t_bool	d_quote;

	i = 0;
	start = 0;
	end = 0;
	name = NULL;
	content = NULL;
	d_quote = FALSE;
	if (type == 1)
	{
		while (cmd->arg[i] != '$' && cmd->arg[i + 1] != '?')
			i++;
		start = i + 1;
		end = start + 1;
		content = ft_itoa(t_envp->utils->return_code);
	}
	else if (type == 2)
	{
		while (cmd->arg[i])
		{
			if (cmd->arg[i] == '"')
			{
				d_quote = TRUE;
				i++;
			}
			if (cmd->arg[i] == '\'' && d_quote == FALSE)
			{
				i++;
				while (cmd->arg[i] != '\'')
					i++;
			}
			else if (cmd->arg[i] == '"')
			{
				d_quote = FALSE;
				i++;
			}
			if (cmd->arg[i] == '$')
			{
				start = i;
				i++;
				while ((cmd->arg[i] >= 'a' && cmd->arg[i] <= 'z') || (cmd->arg[i] >= 'A' && cmd->arg[i] <= 'Z')
						|| (cmd->arg[i] >= '0' && cmd->arg[i] <= '9'))
					i++;
				end = i;
				name = ft_substr(cmd->arg, start + 1, end - start - 1);
				content = ft_getenv(name, t_envp, 0);
				start++;
				break ;
			}
			i++;
		}
	}
	else if (type == 3)
	{
		content = "";
		start = 0;
		end = 0;
	}
	else
	{
		content = "";
		start = 0;
		end = 0;
	}
	if (!content)
		content = "";
	ft_expand_do(cmd, ft_substr(content, 0, ft_strlen(content)), start, end - 1);
}

