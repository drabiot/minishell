/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:12:56 by adorlac           #+#    #+#             */
/*   Updated: 2024/07/30 16:06:16 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*static int	ft_have_expand(char *arg, t_cmd *tmp, t_glob *t_envp)
{
	int		i;

	i = 0;
	(void)t_envp;
	(void)tmp;
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			i++;
			while (arg[i] != '\'')
				i++;
		}
		//if (arg)
		//if (arg[i] == '$' && arg[i + 1] && (arg[i + 1] != ' '
		//		&& arg[i + 1] != '"' && arg[i + 1] != '\''))
		if (arg[i] == '$')
		{
			i++;
			while (arg[i])
			{
				if (!(!(arg[i] >= 'a' && arg[i] <= 'z') && (arg[i] != '?') &&
					!(arg[i] >= 'A' && arg[i] <= 'Z') &&
						arg[i] != '_' && !(arg[i] >= '0' && arg[i] <= '9')))
					return (1);
				if (arg[i - 1] != '\0' && arg[i - 2] != '"' && arg[i] != '"')
					return (1);
				i++;
			}
		}
		else
			i++;
	}
	return (0);
}

void	ft_expand(t_cmd **list, t_glob *t_envp)
{
	t_cmd	*tmp;
	t_cmd	*t_next;

	tmp = *list;
	t_next = ft_lstnew_cmd(NULL, 0, 0);
	if (!t_next)
		return ;
	while (tmp)
	{
		while (ft_have_expand(tmp->arg, tmp, t_envp)
			&& !ft_verif_main(tmp->arg))
		{
			t_next->next = tmp->next;
			ft_expand_modif_main(tmp, t_envp);
		}
		if (!(ft_have_expand(tmp->arg, tmp, t_envp)
				&& !ft_verif_main(tmp->arg)))
			tmp = tmp->next;
		else
			tmp = t_next;
	}
	//ft_lstclear_cmd(&t_next);
}*/

static t_bool	other_expand(char *arg, int **type, int i)
{
	int	quote;

	quote = -1;
	if (arg[i - 1] == '"' || arg[i - 1] == '\'')
		quote = i - 1;
	if (arg[i + 1] == '\0' || arg[i + 1] == ' ' || (arg[i + 1] == arg[quote] && quote != -1) || arg[i + 1] == '=' || arg[i + 1] == '.')
	{
		**type = 3;
		return (FALSE);
	}
	while (arg[i])
	{
		//if (arg[i] == '"' || arg[i] == '\'')
		//	quote = i;
		if (!((arg[i] >= 'a' && arg[i] <= 'z') && (arg[i] >= 'A' && arg[i] <= 'Z')
			&& (arg[i] >= '0' && arg[i] <= '9')))
		{
			**type = 2;
			return (TRUE);
		}
		//if (arg[i] == arg[quote] && quote != -1 && i != quote)
		//	quote = -1;
		i++;
	}
	return (FALSE);
}

static t_bool	is_expandable(char *arg, int *type)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			i++;
			while (arg[i] && arg[i] != '\'')
				i++;
		}
		else if (arg[i] == '$')
		{
			if (arg[i + 1] == '?')
			{
				*type = 1;
				return (TRUE);
			}
			else if (other_expand(arg, &type, i))
				return (TRUE);
			else
				return (FALSE);
		}
		else
			i++;
	}
	return (FALSE);
}

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
	free(list->arg);
	list->arg = full;
	if (first_part)
		free(first_part);
	if (end_part)
		free(end_part);
	if (content)
		free(content);
	if (with_content)
		free(with_content);
}

static void	ft_expand_modif(t_cmd *cmd, t_glob *t_envp, int type)
{
	int		i;
	int		start;
	int		end;
	char	*content;
	char	*name;

	i = 0;
	start = 0;
	end = 0;
	name = NULL;
	content = NULL;
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
			if (cmd->arg[i] == '\'')
			{
				i++;
				while (cmd->arg[i] != '\'')
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


void	ft_expand(t_cmd **list, t_glob *t_envp)
{
	t_cmd	*tmp;
	int		type;

	tmp = *list;
	type = 0;
	while (tmp)
	{
		while (is_expandable(tmp->arg, &type))
			ft_expand_modif(tmp, t_envp, type);
		tmp = tmp->next;
	}
}
