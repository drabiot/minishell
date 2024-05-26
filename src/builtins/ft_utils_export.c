/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:36:39 by nberduck          #+#    #+#             */
/*   Updated: 2024/05/26 18:57:02 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_delete_quote(char *str)
{
	char	**split_part;
	char	*tmp;

	split_part = ft_split(str, '"');
	tmp = ft_strjoin(split_part[0], split_part[1]);
	printf("%s\n", tmp);
	return (tmp);
}

static int	ft_find_quote(t_cmd *arg)
{
	unsigned int	i;
	int				double_quote;
	unsigned int	first_quote;
	
	double_quote = 0;
	i = 0;
	while (arg->arg[i])
	{
		if (double_quote == 1 && arg->arg[i] == '"' && arg->arg[i + 1])
			return (1);
		if (arg->arg[i] == '"')
		{
			first_quote = i;
			double_quote = 1;
		}
		i++;
	}
	if (double_quote == 1)
		arg->arg = ft_delete_quote(arg->arg);
	return (0);
}

int	ft_check_quote_and_delete(t_cmd **args)
{
	t_cmd		*tmp;
	
	tmp = *args;
	while (tmp)
	{
		if (ft_find_quote(tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_glob  *ft_globsolo_creation(char *arg)
{
	t_glob			*tmp;
	char           *name;
	char           *content;
	int            name_end;

	name_end = ft_name_len(arg);
    name = ft_substr(arg, 0, name_end);
    content = ft_substr(arg, name_end + 1, ft_strlen(arg));
    if (arg[name_end] && arg[name_end] == '=')
       tmp = ft_lstnew_glob(name, 1, content);
    else
       tmp = ft_lstnew_glob(name, 0, content);
   return (tmp);
}
