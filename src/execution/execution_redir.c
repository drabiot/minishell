/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:33:04 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/20 16:39:12 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*grab_redir(t_cmd *cmd, t_exec *node, int type, int file, t_glob *glob)
{
	int	fd;

	fd = -1;
	if (file == 0 && type == 0 && node->file_error == FALSE)
	{
		if (cmd->next)
			fd = open(cmd->next->arg, O_RDONLY);
		else
		{
			node->file_error = TRUE;
			ft_putstr_fd(" unexpected token\n", 2);
		}
		if (fd == -1 && node->file_error == FALSE)
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
		if (fd != -1)
			close(fd);
	}
	else if (file == 1 && type == 0 && node->file_error == FALSE)
	{
		if (cmd->next)
		{
			if (cmd->type == APPEND_REDIR)
				fd = open(cmd->next->arg, O_WRONLY | O_APPEND | O_CREAT, 0644);
			else if (cmd->type == TRUNC_REDIR)
				fd = open(cmd->next->arg, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
		else
		{
			node->file_error = TRUE;
			ft_putstr_fd(" unexpected token\n", 2);
		}
		if (fd == -1 && node->file_error == FALSE)
		{
			if (access(cmd->next->arg, F_OK) != 0)
			{
				ft_putstr_fd(" No such file or directory\n", 2);
				glob->utils->return_code = 127;
			}
			else
			{
				ft_putstr_fd(" Permission denied\n", 2);
				glob->utils->return_code = 126;
			}
			node->file_error = TRUE;
		}
		if (fd != -1)
			close(fd);
	}
	if (type == 0)
	{
		if (!cmd || !cmd->next)
			return (NULL);
		if (cmd->next)
			return (ft_strdup(cmd->next->arg));
	}
	else if (type == 1)
	{
		if (cmd->type == APPEND_REDIR)
			return ("append");
		else if (cmd->type == TRUNC_REDIR)
			return ("trunc");
	}
	return (NULL);
}
