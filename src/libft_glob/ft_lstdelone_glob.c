/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_glob.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:22:49 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/15 11:31:14 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstdelone_glob(t_glob *lst)
{
	if (!lst)
		return ;
	if (lst->name)
		free(lst->name);
	if (lst->content)
		free(lst->content);
	free(lst);
}
