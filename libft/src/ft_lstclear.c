/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:26:39 by tchartie          #+#    #+#             */
/*   Updated: 2023/11/06 23:33:41 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*
** Deletes and frees the given node and every
** successor of that node, using the function ’del’ and free.
** Finally, the pointer to the list must be set to NULL
*/
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*array;

	if (lst)
	{
		while (*lst)
		{
			array = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = array;
		}
	}
}
