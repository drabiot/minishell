/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 21:53:31 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/01 12:08:23 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	write_syntax_error(t_cmd *cmd, t_input *line, t_glob *t_envp)
{
	char	*token;

	token = NULL;
	if (cmd)
		token = cmd->arg;
	if (token && line->str)
	{
		ft_putstr_fd(" syntax error near unexpected token `", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd("'\n `", 2);
		ft_putstr_fd(line->str, 2);
		ft_putstr_fd("'\n", 2);
		t_envp->utils->return_code = 2;
	}
}

static t_bool	multi_error(t_cmd *cmd, t_cmd *prev)
{
	if (!prev)
		return (FALSE);
	if (prev->type == HERE_DOC && (!cmd || cmd->type != LIMITER))
		return (TRUE);
	if (prev->type == PIPE && (!cmd || cmd->type == PIPE))
		return (TRUE);
	if ((prev->type == APPEND_REDIR || prev->type == TRUNC_REDIR
			|| prev->type == INPUT) && (!cmd || cmd->type == PIPE
		|| cmd->type == APPEND_REDIR || cmd->type == TRUNC_REDIR
			|| cmd->type == INPUT || cmd->type == HERE_DOC))
		return (TRUE);
	return (FALSE);
}

static void	check_pipe_start(t_cmd *cmd, t_cmd **prev, t_bool *error)
{
	if (!cmd)
		return ;
	if (cmd->type == PIPE)
	{
		*prev = cmd;
		*error = TRUE;
	}
}

t_bool is_error_syntax(t_cmd *cmd, t_glob *t_envp, t_input *line)
{
    t_cmd	*prev;
	t_bool	error;

	prev = NULL;
	error = FALSE;
	check_pipe_start(cmd, &prev, &error);
    if (cmd)
	{
    	prev = cmd;
		cmd = cmd->next;
	}
    while (prev && error == FALSE)
    {
        error = multi_error(cmd, prev);
		if (!cmd)
			break ;
		prev = cmd;
        cmd = cmd->next;
    }
	if (error)
	{
		write_syntax_error(prev, line, t_envp);
		return (TRUE);
	}
	return (FALSE);
}
