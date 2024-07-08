/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_modif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:50:01 by adorlac           #+#    #+#             */
/*   Updated: 2024/07/05 12:07:12 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	ft_expand_modif(t_cmd *list, char *content, int start, int end)
{
	char	*first_part;
	char	*end_part;
	char	*with_content;
	char	*full;

	first_part = ft_substr(list->arg, 0, start - 1);
	end_part = ft_substr(list->arg, end + 2, ft_strlen(list->arg) - end);
	if (!content)
		full = ft_strjoin(first_part, end_part);
	else
	{
		with_content = ft_strjoin(first_part, content);
		full = ft_strjoin(with_content, end_part);
	}
	// printf("1 : %s\n", first_part);
	// printf("2 : %s\n", content);
	// printf("3 : %s\n", end_part);
	// printf("4 : %s\n", full);
	free(list->arg);
	list->arg = full;
	free(first_part);
	free(end_part);
	if (content)
		free(with_content);
}

char	*ft_getenv(char *name, t_list *t_envp)
{
	t_list	*tmp;
	char	*name_var;
	char	*name_tmp;
	char	*content;
	int		i;

	tmp = t_envp;
	while (tmp)
	{
		i = 0;
		name_tmp = (char *)tmp->content;
		while (name_tmp && name_tmp[i] != '=')
			i++;
		name_var = ft_substr(name_tmp, 0, i);
		if (!ft_strcmp(name_var, name))
		{
			content = ft_substr(name_tmp, i + 1, ft_strlen(name_tmp) - i);
			free(name_tmp);
			free(name_var);
			return (content);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_expand_modif_main(t_cmd *list, t_list *t_envp)
{
	int		i;
	int		start;
	int		end;
	char	*name;
	char	*content;

	i = 0;
	while (list->arg[i] && list->arg[i] != '$')
		i++;
	start = ++i;
	while (list->arg[i] && i != 0)
	{
		if (!(list->arg[i + 1] >= 'a' && list->arg[i + 1] <= 'z') &&
			!(list->arg[i + 1] >= 'A' && list->arg[i + 1] <= 'Z') &&
			list->arg[i + 1] != '_' && !(list->arg[i + 1] >= '0' && list->arg[i + 1] <= '9'))
		{
			end = i - 1;
			i = -1;
		}
		i++;
	}
	name = ft_substr(list->arg, start, end - start + 2);
	printf("%s\n", name);
	content = ft_getenv(name, t_envp);
	ft_expand_modif(list, content, start, end);
}
