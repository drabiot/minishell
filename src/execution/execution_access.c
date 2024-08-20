/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_access.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:25:49 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/20 19:38:45 by tchartie         ###   ########.fr       */
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
	if (!all_path || (access(cmd, X_OK) == 0 || is_builtins(cmd)
			|| cmd[0] == '\0' || is_path))
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

static char	*create_tmp_cmd(char *arg, t_bool is_path)
{
	char	*tmp_cmd;

	tmp_cmd = NULL;
	if (arg && is_builtins(arg))
		tmp_cmd = ft_strdup(arg);
	else if ((arg && is_path) || (arg && arg[0] == '\0'))
		tmp_cmd = ft_strdup(arg);
	else if (arg)
		tmp_cmd = ft_strjoin("/", arg);
	return (tmp_cmd);
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
	tmp_cmd = create_tmp_cmd(arg, is_path);
	full_path = get_cor_path(tmp_cmd, content_path, is_path, 0);
	if (tmp_cmd)
		free(tmp_cmd);
	if (!full_path)
		return (NULL);
	return (full_path);
}

static t_bool	fill_flags(t_cmd *cmd, char **flags, int i)
{
	if (cmd->arg && (cmd->type == COMMAND || cmd->type == WORD
			|| cmd->type == PATH || cmd->type == NONE))
	{
		flags[i] = ft_strdup(cmd->arg);
		return (TRUE);
	}
	return (FALSE);
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
		if (fill_flags(cmd, flags, i))
			i++;
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
