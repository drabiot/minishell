/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:44:59 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/25 10:34:22 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

static int	is_path(t_cmd *current, t_cmd *prev)
{
	if (prev && (prev->type == HERE_DOC || prev->type == INPUT
			|| prev->type == APPEND_REDIR || prev->type == TRUNC_REDIR))
		return (2);
	if (access(current->arg, X_OK) == 0)
		return (10);
	else if (current->arg && (current->arg[0] == '/'
			|| (current->arg[0] == '.' && current->arg[1] == '/')))
		return (1);
	return (0);
}

int	ft_find_type(char *arg, t_cmd *prev)
{
	static int	limiter = 0;

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
	else if (is_start(prev) || !prev)
		return (COMMAND);
	else
		return (WORD);
}

void expandable_type(t_cmd *exec)
{
	bool	have_cmd;
	t_cmd	*prev;
	int		ret_path;

	have_cmd = FALSE;
	prev = NULL;
	while (exec && exec->next)
	{
		if (ft_strcmp(exec->arg, "") == 0)
			exec->type = NONE;
		ret_path = is_path(exec, prev);
		if (prev && have_cmd == FALSE && (ret_path == 10
			|| (prev->type != WORD && prev->type != COMMAND)))
		{
			exec->type = COMMAND;
			have_cmd = TRUE;
		}
		if (ret_path == 1)
			exec->type = PATH;
		if (ret_path == 2)
			exec->type = REDIR_FILE;
		if (prev && prev->type == PIPE)
			have_cmd = FALSE;
		if (exec->arg[0] == '|')
			exec->type = PIPE;
		prev = exec;
		exec = exec->next;
	}
}
