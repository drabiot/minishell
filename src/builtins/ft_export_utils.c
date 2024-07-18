/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:36:39 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/18 23:09:36 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_delete_quote(char *str)
{
	char	**split_part;
	char	*tmp;

	split_part = ft_split(str, '"');
	tmp = ft_strjoin(split_part[0], split_part[1]);
	// printf("%s\n", tmp);
	return (tmp);
}

int	ft_check_quote_and_delete(t_exec **exec)
{
	unsigned int	i;
	int				double_quote;
	unsigned int	first_quote;

	double_quote = 0;
	i = 0;
	while ((*exec)->flags[1][i])
	{
		if (double_quote == 1 && (*exec)->flags[1][i] == '"' && (*exec)->flags[1][i + 1])
			return (1);
		if ((*exec)->flags[1][i] == '"')
		{
			first_quote = i;
			double_quote = 1;
		}
		i++;
	}
	if (double_quote == 1)
		(*exec)->flags[1] = ft_delete_quote((*exec)->flags[1]);
	return (0);
}

t_glob	*ft_globsolo_creation(char *arg)
{
	t_glob	*tmp;
	char	*name;
	char	*content;
	int		name_end;

	name_end = ft_name_len(arg);
	name = ft_substr(arg, 0, name_end);
	content = ft_substr(arg, name_end + 1, ft_strlen(arg));
	//redo miss env variable
	if (arg[name_end] && arg[name_end] == '=')
		tmp = ft_lstnew_glob(name, 1, content, NULL);
	else
		tmp = ft_lstnew_glob(name, 0, content, NULL);
	return (tmp);
}
