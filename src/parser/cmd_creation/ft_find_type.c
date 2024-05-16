/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:44:59 by nberduck          #+#    #+#             */
/*   Updated: 2024/05/16 17:07:00 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*static int ft_is_cmd(char *arg)
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
}*/

static int	is_start(t_cmd *prev)
{
	if (!prev)
		return (0);
	if (prev->type == PIPE || prev->type == LIMITER
		|| prev->type == REDIR_FILE)
		return (1);
	return (0);
}

static int	is_redir(t_cmd *prev)
{
	if (!prev)
		return (0);
	if (prev->type == INPUT || prev->type == TRUNC_REDIR
		|| prev->type == APPEND_REDIR)
		return (1);
	return (0);
}

int	ft_find_type(char *arg, t_cmd *prev)
{
	static int limiter = 0;
	
	if (limiter == 1)
	{
		limiter = 0;
		return (LIMITER);
	}
	else if (arg[0] == '|')
		return (PIPE);
	else if (arg[0] == '<' && arg[1] == '<')
	{
		limiter = 1;
		return (HERE_DOC);
	}
	else if (arg[0] == '<')
		return (INPUT);
	else if (arg[0] == '>' && arg[1] == '>')
		return (APPEND_REDIR);
	else if (arg[0] == '>')
		return (TRUNC_REDIR);
	else if (is_redir(prev))
		return (REDIR_FILE);
	else if (prev && (prev->type == REDIR_FILE || prev->type == INFILE))
		return (INFILE);
	else if (is_start(prev) || !prev)
		return (COMMAND);
	else
		return (WORD);
}
