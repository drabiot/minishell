/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:44:59 by nberduck          #+#    #+#             */
/*   Updated: 2024/04/04 20:56:23 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int ft_is_cmd(char *arg)
{
	if (!ft_strcmp(arg, "echo"))
		return (1);
	if (!ft_strcmp(arg, "cd"))
		return (1);
	if (!ft_strcmp(arg, "pwd"))
		return (1);
	if (!ft_strcmp(arg, "export"))
		return (1);
	if (!ft_strcmp(arg, "unset"))
		return (1);
	if (!ft_strcmp(arg, "env"))
		return (1);
	if (!ft_strcmp(arg, "exit"))
		return (1);
	if (!ft_strcmp(arg, "$?"))
		return (1);
	return (0);
}

int	ft_find_type(char *arg)
{
	static int limiter = 0;
	
	if (limiter == 1)
	{
		limiter = 0;
		return (LIMITER);
	}
	if (arg[0] == '|')
		return (PIPE);
	if (arg[0] == '<' && arg[1] == '<')
	{
		limiter = 1;
		return (HERE_DOC);
	}
	if (arg[0] == '<')
		return (INPUT);
	if (arg[0] == '>' && arg[1] == '>')
		return (APPEND_REDIR);
	if (arg[0] == '>')
		return (TRUNC_REDIR);
	if (ft_is_cmd(arg))
		return (COMMAND);
	return (WORD);
}
