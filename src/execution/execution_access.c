/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_access.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:25:49 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/20 15:29:23 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_cor_path(char *cmd, char *content_path, t_bool is_path, int i)
{
	char	**all_path;
	int		access_state;
	char	*correct_path;

	all_path = ft_split((char const *)content_path, ':');
	access_state = 1;
	if (!all_path || (access(cmd, X_OK) == 0 || is_builtins(cmd) || cmd[0] == '\0' || is_path))
	{
		correct_path = ft_strdup(cmd);
		free_paths(all_path);
		return (correct_path);
	}
	while (all_path[i] && access_state != 0)
	{
		correct_path = ft_strjoin(all_path[i], cmd);
		if (!correct_path)
			return (NULL);
		access_state = access(correct_path, X_OK);
		i++;
		if (all_path[i] && access_state != 0)
			free(correct_path);
	}
	free_paths(all_path);
	return (correct_path);
}

char	*get_cmd(char *arg, t_glob *glob)
{
	t_glob	*path;
	char	*content_path;
	char	*full_path;
	char	*tmp_cmd;
	t_bool	is_path;

	path = NULL;
	content_path = NULL;
	tmp_cmd = NULL;
	if (glob)
		path = glob;
	if (!arg)
		return (NULL);
	is_path = ft_strchr(arg, '/') != NULL;
	while (path && ft_strcmp(path->name, "PATH") != 0)
		path = path->next;
	if (path)
		content_path = path->content;
	if (arg && is_builtins(arg))
		tmp_cmd = ft_strdup(arg);
	else if (arg && ((access(arg, X_OK) == 0) || (arg[0] == '\0')) && is_path)
		tmp_cmd = ft_strdup(arg);
	else if (arg)
		tmp_cmd = ft_strjoin("/", arg); //strdup arg et "/"
	full_path = get_cor_path(tmp_cmd, content_path, is_path, 0);
	if (tmp_cmd)
		free(tmp_cmd);
	if (!full_path)
		return (NULL);
	return (full_path);
}

char	**get_flags(t_cmd *cmd, char *path)
{
	int		i;
	char	*line;
	char	**flags;

	i = 0;
	line = NULL;
	flags = ft_calloc(sizeof(char *), ft_lstsize_cmd(cmd) + 1);
	if (!flags)
		return (NULL);
	while (cmd && cmd->type != PIPE)
	{
		if (cmd->arg && (cmd->type == COMMAND || cmd->type == WORD || cmd->type == PATH || cmd->type == NONE))
		{
			flags[i] = ft_strdup(cmd->arg);
			i++;
		}
		cmd = cmd->next;
	}
	if (!path && (!flags || !*flags))
	{
		if (flags)
			free (flags);
		return (NULL);
	}
	free(flags[0]);
	flags[0] = path;
	return (flags);
}

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
			if (access(cmd->next->arg, F_OK) >= 0 && access(cmd->next->arg, X_OK) < 0)
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