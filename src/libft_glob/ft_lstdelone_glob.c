/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_glob.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:22:49 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/23 10:24:58 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstdelone_glob(t_glob *lst)
{
	
	if (!lst)
		return ;
	free(lst->name);
	free(lst->content);
	free(lst);
}
