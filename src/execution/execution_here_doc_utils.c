/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_here_doc_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:42:33 by nberduck          #+#    #+#             */
/*   Updated: 2024/07/09 15:05:41 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static char	*ft_get_var_name(char *line)
{
	char	*tmp;
	int		i;
	int		start;
	int		end;
	int		start_ok;

	i = 0;
	start_ok = 0;
	end = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			start = i + 1;
			start_ok = 1;
		}
		if (line[i] == ' ' && start_ok)
			end = i - 1;
		i++;
	}
	if (end == 0)
		end = ft_strlen(line) - 2;
	tmp = ft_substr(line, start, end - start + 1);
	// printf("start :%i, end:%i, tmp: %s\n", start, end, tmp);
	return (tmp);
}

static char	*ft_expand_name(char *content, char *line)
{
	char	*first_part;
	char	*with_content;
	char	*return_value;
	int		i;

	i = 0;
	while (line[i] && line[i] != '$')
		i++;
	if (i == 0)
		first_part = NULL;
	else
		first_part = ft_substr(line, 0, i);
	with_content = ft_strjoin(first_part, content);
	free(first_part);
	while (line[i] && line[i] != ' ' && line[i] != '\n')
		i++;
	if (!line[i])
		return (with_content);
	return_value = ft_strjoin(with_content, &line[i]);
	free(with_content);
	return (return_value);
}

static char	*ft_expand_name_null(char *line)
{
	char	*first_part;
	char	*return_value;
	int		i;

	i = 0;
	while (line[i] && line[i] != '$')
		i++;
	if (i == 0)
		first_part = NULL;
	else
		first_part = ft_substr(line, 0, i - 1);
	while (line[i] && line[i] != ' ' && line[i] != '\n')
		i++;
	if (!line[i])
		return (first_part);
	return_value = ft_strjoin(first_part, &line[i]);
	free(first_part);
	return (return_value);
}

char	*ft_expand_line(t_glob **t_list, char *line)
{
	char	*return_value;
	char	*name;
	t_glob	*tmp;

	if (!ft_have_expand(line))
		return (line);
	name = ft_get_var_name(line);
	// printf("%s\n", name);
	tmp = *t_list;
	while (tmp)
	{
		// printf("%s\n", tmp->name);
		if (!ft_strcmp(tmp->name, name))
		{
			// printf("%s\n", tmp->content);
			return_value = ft_expand_name(tmp->content, line);
			free(line);
			return (return_value);
		}
		tmp = tmp->next;
	}
	return_value = ft_expand_name_null(line);
	free(line);
	return (return_value);
}
