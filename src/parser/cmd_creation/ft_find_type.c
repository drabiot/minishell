/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:44:59 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/14 16:22:20 by adorlac          ###   ########.fr       */
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
	if (!current->arg)
		return (0);
	if (prev && (prev->type == INPUT || prev->type == APPEND_REDIR
			|| prev->type == TRUNC_REDIR))
		return (2);
	if (prev && prev->type == HERE_DOC)
		return (3);
	if (ft_strchr(current->arg, '/'))
		return (1);
	else
		return (10);
	/*if (access(current->arg, F_OK) == 0)
		return (10);*/
	// else if (current->arg && (current->arg[0] == '/'
	// 		|| (current->arg[0] == '.' && current->arg[1] == '/')))
	// 	return (1);
	return (0);
}

int	ft_find_type(char *arg, t_cmd *prev)
{
	if (prev && prev->type == HERE_DOC)
		return (LIMITER);
	else if (arg[0] == '|')
		return (PIPE);
	else if (arg[0] == '<' && arg[1] == '<')
		return (HERE_DOC);
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

void	expendable_type_mid(t_cmd *exec, int ret, bool *have_cmd, t_cmd *prev)
{
	if (exec->arg && exec->arg[0] == '<' && exec->arg[1] == '\0')
		exec->type = INPUT;
	else if (exec->arg && exec->arg[0] == '>' && exec->arg[1] == '>')
		exec->type = APPEND_REDIR;
	else if (exec->arg && exec->arg[0] == '>')
		exec->type = TRUNC_REDIR;
	else if (ret == 3)
		exec->type = LIMITER;
	else if ((ret != 2) && (exec->type == COMMAND || (prev && *have_cmd == FALSE
				&& (prev->type != WORD && prev->type != COMMAND))))
	{
		exec->type = COMMAND;
		*have_cmd = TRUE;
	}
}

void	expandable_type(t_cmd *exec)
{
	bool	have_cmd;
	t_cmd	*prev;
	int		ret_path;

	have_cmd = FALSE;
	prev = NULL;
	while (exec && exec->next)
	{
		if (!exec->arg && exec->next)
			exec->type = NONE;
		ret_path = is_path(exec, prev);
		if (ret_path == 2)
			exec->type = REDIR_FILE;
		expendable_type_mid(exec, ret_path, &have_cmd, prev);
		if (exec->arg && exec->arg[0] == '|')
		{
			exec->type = PIPE;
			have_cmd = FALSE;
		}
		prev = exec;
		exec = exec->next;
	}
}
