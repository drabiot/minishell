/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_modif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:50:01 by nberduck          #+#    #+#             */
/*   Updated: 2024/06/19 20:02:12 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_last_return(void)
{
	char	*tmp;

	tmp = NULL;
	return (tmp);	
}

static void ft_expand_modif(t_cmd *list, char *content, int start, int end)
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
	free(list->arg);
	list->arg = full;
	free(first_part);
	free(end_part);
	if (content)
	{
		free(content);
		free(with_content);
	}
	list->arg = full;
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
	content = ft_getenv(name, t_envp, 0);
	// printf("%s\n", content);
	free(name);
	ft_expand_modif(list, content, start, end);
}
