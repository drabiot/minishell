/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_modif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:50:01 by adorlac           #+#    #+#             */
/*   Updated: 2024/07/30 13:07:48 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_last_return(void)
{
	char	*tmp;

	tmp = NULL;
	return (tmp);
}

static void	ft_expand_modif(t_cmd *list, char *content, int start, int end)
{
	char	*first_part;
	char	*end_part;
	char	*with_content;
	char	*full;

	with_content = NULL;
	first_part = ft_substr(list->arg, 0, start - 1);
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

char	*ft_getenv(char *name, t_glob *t_envp, int i)
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

void	ft_expand_modif_main(t_cmd *list, t_glob *t_envp)
{
	int		i;
	int		start;
	int		end;
	char	*name;
	char	*content;

	i = 0;
	while (list->arg[i] && list->arg[i] != '$')
	{
		if (list->arg[i] != '\'')
		{
			i++;
			while (list->arg && list->arg[i] == '\'')
				i++;
		}
		else
			i++;
	}
	start = ++i;
	end = start;
	while (list->arg[i] && i != 0)
	{
		if (i == start && list->arg[i] == '?')
		{
			end = i + 1;
			break ;
		}
		if (list->arg[i] == '\'')
		{
			i++;
			while (list->arg[i] != '\'')
				i++;
		}
		if (!(list->arg[i] >= 'a' && list->arg[i] <= 'z') &&
			!(list->arg[i] >= 'A' && list->arg[i] <= 'Z') &&
			list->arg[i] != '_' && !(list->arg[i] >= '0' && list->arg[i] <= '9'))
		{
			end = i;
			break ;
		}
		i++;
	}
	printf("start: %d, end: %d\n", start, end);
	if (!list->arg[i])
		end = i;
	if (start == end && (list->arg[start] != '?' || (list->arg[end] != '\0' && list->arg[end - 1] != '"' && list->arg[end + 1] != '"')))
	{
		if (start > 1)
			start--;
		name = NULL;
		content = NULL;
	}
	else
		name = ft_substr(list->arg, start, end - start);
	if (name && !ft_strncmp(name, "?", 1))
		content = ft_itoa(t_envp->utils->return_code);
	else if (name)
		content = ft_getenv(name, t_envp, 0);
	if (!content)
		content = "";
	// printf("start: %d, end: %d, i: %d\n", start, end, i);
	// printf("name: %s, content: %s\n", name, content);
	free(name);
	ft_expand_modif(list, ft_substr(content, 0, ft_strlen(content)), start, end - 1);
}
