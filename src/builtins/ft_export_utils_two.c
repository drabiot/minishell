/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:39:22 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/16 16:51:36 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	change_glob_sign(char *glob, int start_content)
{
	if (glob[start_content] == '+' && glob[start_content + 1] == '=')
		start_content++;
	if (glob[start_content == '='])
		start_content++;
	return (start_content);
}

void	change_glob_two(t_glob *list, char *name, char *content, char *tmp_con)
{
	while (list && ft_strcmp(name, list->name) != 0)
		list = list->next;
	list->equal = 1;
	tmp_con = ft_strdup(list->content);
	free(list->content);
	list->content = ft_strjoin(tmp_con, content);
	free(content);
	free(tmp_con);
}

void	change_glob_one(t_glob *list, char *name, char *content)
{
	while (list && ft_strcmp(name, list->name) != 0)
		list = list->next;
	list->equal = 1;
	if (list->content)
		free(list->content);
	list->content = content;
}
