/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_modif_utils_two.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:07:20 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/16 16:15:19 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

void	free_expand_do(char *a, char *b, char *c, char *d)
{
	if (a)
	{
		free(a);
		a = NULL;
	}
	if (b)
	{
		free(b);
		b = NULL;
	}
	if (c)
	{
		free(c);
		c = NULL;
	}
	if (d)
	{
		free(d);
		d = NULL;
	}
}

void	free_char(char **c)
{
	if (*c)
	{
		free(*c);
		*c = NULL;
	}
}

void	ft_expd_do(t_cmd *list, char *content, int start, int end)
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
	free_char(&full);
	//list->arg = full;
	free_expand_do(first_part, end_part, content, with_content);
}
