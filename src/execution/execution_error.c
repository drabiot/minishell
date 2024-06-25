/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:41:30 by nberduck          #+#    #+#             */
/*   Updated: 2024/06/25 11:49:52 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
	
void	ft_errno(void)
{
	char	*error;
	
	error = strerror(errno);
	ft_putstr_fd(error, 2);
}