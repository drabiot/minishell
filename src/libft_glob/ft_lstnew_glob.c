/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_glob.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:41:40 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/16 19:57:07 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_glob	*ft_lstnew_glob(char *name, int equal, char *content, char **env)
{
	t_glob	*array;

	array = (t_glob *)malloc(sizeof(t_glob));
	if (!array)
		return (NULL);
	array->next = NULL;
	array->name = name;
	array->equal = equal;
	array->content = content;
	array->env = env;
	return (array);
}
