/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_process_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:57:15 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/20 16:59:11 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_error_quit(t_exec *list, t_glob **t_envp, int code, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	free_exit(list, *t_envp);
	exit(code);
}
