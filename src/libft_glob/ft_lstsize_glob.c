/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_glob.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:16:13 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/19 19:11:54 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_lstsize_glob(t_glob *glob)
{
	int	i;

	i = 0;
	while (glob)
	{
		if (glob->equal == 1)
			i++;
		glob = glob->next;
	}
	return (i);
}