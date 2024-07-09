/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:41:30 by nberduck          #+#    #+#             */
/*   Updated: 2024/07/09 14:55:23 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_errno(void)
{
	char	*error;

	error = strerror(errno);
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}
