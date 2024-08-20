/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:33:04 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/20 23:39:08 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_file_err(int *fd, t_cmd *cmd, t_exec *node, t_glob *glob)
{
	if (*fd == -1 && !node->file_error)
	{
		if (access(cmd->next->arg, F_OK) >= 0
			&& access(cmd->next->arg, X_OK) < 0)
		{
			ft_errno();
			glob->utils->return_code = 126;
		}
		else if (access(cmd->next->arg, F_OK) < 0)
		{
			ft_errno();
			glob->utils->return_code = 127;
		}
		node->file_error = TRUE;
	}
	if (*fd != -1)
		close(*fd);
}

void	handle_redir_type_0(int *fd, t_cmd *cmd, t_exec *node, t_glob *glob)
{
	if (cmd->next)
		*fd = open(cmd->next->arg, O_RDONLY);
	else
	{
		node->file_error = TRUE;
		ft_putstr_fd(" unexpected token\n", 2);
	}
	handle_file_err(fd, cmd, node, glob);
}

void	handle_redir_type_1(int *fd, t_cmd *cmd, t_exec *node, t_glob *glob)
{
	if (cmd->next)
	{
		if (cmd->type == APPEND_REDIR)
			*fd = open(cmd->next->arg, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (cmd->type == TRUNC_REDIR)
			*fd = open(cmd->next->arg, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	else
	{
		node->file_error = TRUE;
		ft_putstr_fd(" unexpected token\n", 2);
	}
	handle_file_err(fd, cmd, node, glob);
}

char	*grab_redir(t_cmd *cmd, t_exec *node, int type, t_glob *glob)
{
	int	fd;

	fd = -1;
	if (type == 0 && !node->file_error)
		handle_redir_type_0(&fd, cmd, node, glob);
	else if (type == 1 && !node->file_error)
		handle_redir_type_1(&fd, cmd, node, glob);
	if (type == 0 || type == 1)
	{
		if (!cmd || !cmd->next)
			return (NULL);
		return (ft_strdup(cmd->next->arg));
	}
	if (type == 11)
	{
		if (cmd->type == APPEND_REDIR)
			return ("append");
		if (cmd->type == TRUNC_REDIR)
			return ("trunc");
	}
	return (NULL);
}
