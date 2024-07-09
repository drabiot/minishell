/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:36:16 by nberduck          #+#    #+#             */
/*   Updated: 2024/07/10 00:05:15 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_find_redir(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == APPEND_REDIR)
			return (1);
		if (tmp->type == TRUNC_REDIR)
			return (2);
		if (tmp->type == INPUT)
			return (3);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_execution_cmd(int fd, t_glob **t_envp, t_cmd *cmd)
{
	pid_t	pid;
	int		return_value;
	int		ret;

	return_value = ft_find_builtins_part1(fd, t_envp, cmd);
	if (return_value != -1)
		return (return_value);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		if (ft_have_heredoc(cmd))
			return_value = ft_here_doc(t_envp, cmd);
		else
		{
			return_value = ft_find_redir(cmd);
			if (return_value == 1)
				return_value = ft_append_redir(t_envp, cmd);
			else if (return_value == 2)
				return_value = ft_trunc_redir(t_envp, cmd);
			else if (return_value == 3)
				return_value = ft_input_redir(t_envp, cmd);
			else
				return_value = ft_execute_other_cmd(t_envp, cmd);
		}
		exit(return_value);
	}
	waitpid(pid, &ret, 0);
	ret = WEXITSTATUS(ret);
	(*t_envp)->utils->return_code = ret;
	printf("ret: %d, code: %d\n", ret, (*t_envp)->utils->return_code);
	return (0);
}

static void set_base_exec(t_exec *current_node, int nb_cmd, int pos_cmd)
{
	current_node->nb_cmd = nb_cmd;
	current_node->pos_cmd = pos_cmd + 1;
	current_node->infile = NULL;
	current_node->outfile = NULL;
	current_node->cmd = NULL;
	current_node->flags = NULL;
	current_node->have_heredoc = 0;
	current_node->limiter = NULL;
	current_node->next = NULL;
}
static char	*get_correct_path(char *cmd, char *content_path)
{
	char	**all_path;
	int		i;
	int		access_state;
	char	*correct_path;

	all_path = ft_split((char const *)content_path, ':');
	i = 0;
	access_state = 1;
	if (access(cmd, X_OK) == 0)
	{
		correct_path = ft_strdup(cmd);
		return (correct_path);
	}
	while (all_path[i] && access_state != 0)
	{
		correct_path = ft_strjoin(ft_strdup(all_path[i]), ft_strdup(cmd));
		if (!correct_path)
			return (NULL);
		access_state = access(correct_path, X_OK);
		i++;
		if (all_path[i] && access_state != 0)
			free(correct_path);
	}
	return (correct_path);
}

static char	*get_cmd(char *arg, t_glob *glob)
{
	t_glob	*path;
	char	*content_path;
	char	*full_path;
	char	*tmp_cmd;

	path = NULL;
	tmp_cmd = NULL;
	if (glob)
		path = glob;
	while (ft_strcmp(path->name, "PATH") != 0)
		path = path->next;
	content_path = path->content;
	if (arg && access(arg, X_OK) == 0)
		tmp_cmd = ft_strdup(arg);
	else if (arg)
		tmp_cmd = ft_strjoin(ft_strdup("/"), ft_strdup(arg));
	full_path = get_correct_path(tmp_cmd, content_path);
	free(tmp_cmd);
	if (!full_path)
		return (NULL);
	return (full_path);
}

static char	**get_flags(t_cmd *cmd, char *path)
{
	int		i;
	char	*line;
	char	**flags;

	i = 0;
	while (cmd && (cmd->type == COMMAND || cmd->type == WORD))
	{
		if (i == 0)
			line = cmd->arg;
		else
		{
			line = ft_strjoin(ft_strdup(line), ft_strdup(" "));
			line = ft_strjoin(ft_strdup(line), ft_strdup(cmd->arg));
		}
		i++;
		cmd = cmd->next;
	}
	flags = ft_split(line, ' ');
	if (!flags || !*flags)
		return (NULL);
	free(flags[0]);
	flags[0] = path;
	return (flags);
}

static char	*grab_redir(t_cmd *cmd)
{
	if (!cmd && !cmd->next)
		return (NULL);
	return (cmd->next->arg);
}

static t_exec	*append_node(t_glob *glob, t_cmd *cmd, int nb_cmd, int pos_cmd)
{
	t_exec	*current_node;

	current_node = malloc(sizeof(t_exec));
	if (!current_node)
		return (NULL);
	set_base_exec(current_node, nb_cmd, pos_cmd);
	while (cmd && cmd->type != PIPE)
	{
		if (current_node->infile == NULL && cmd->type == INPUT)
			current_node->infile = grab_redir(cmd);
		else if (current_node->outfile == NULL && (cmd->type == TRUNC_REDIR
				|| cmd->type == APPEND_REDIR))
			current_node->outfile = grab_redir(cmd);
		else if (current_node->cmd == NULL && cmd->type == COMMAND)
		{
			current_node->cmd = get_cmd(cmd->arg, glob);
			current_node->flags = get_flags(cmd, current_node->cmd);
		}
		else if (cmd->type == HERE_DOC)
			current_node->have_heredoc = 1;
		else if (current_node->limiter == NULL && cmd->type == LIMITER)
			current_node->limiter = cmd->arg;
		cmd = cmd->next;
	}
	return (current_node);
}

static t_exec	*ft_last_node(t_exec *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void	ft_add_back(t_exec **lst, t_exec *new)
{
	t_exec *buffer;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		buffer = ft_last_node((*lst));
		buffer->next = new;
	}
}

static t_exec	*init_exec(t_cmd *cmd, t_glob *t_envp, int len)
{
	t_exec	*last_node;
	t_exec	*current_node;
	t_exec	*first_node;
	int		i;

	last_node = NULL;
	current_node = NULL;
	first_node = NULL;
	i = 0;
	while (i < len)
	{
		current_node = append_node(t_envp, cmd, len, i);
		while (cmd && cmd->type != PIPE)
			cmd = cmd->next;
		while (cmd && cmd->type == PIPE)
			cmd = cmd->next;
		if (!current_node)
		{
			//error
		}
		ft_add_back(&last_node, current_node);
		if (i == 0)
			first_node = last_node;
		i++;
	}
	return(first_node);
}

int	ft_execution_main(t_glob **t_envp, t_cmd *cmd)
{
	int		pipe_len;
	//int		return_value;
	t_exec	*exec;

	if (!cmd)
		return (0);
	pipe_len = ft_pipe_len(cmd);
	exec = init_exec(cmd, *t_envp, pipe_len);
	//while (exec)
	//{
	//printf("EXEC:\nnb_cmd: %d\npos_cmd: %d\ninfile: %s\noutfile: %s\ncmd: %s\nflags: %s %s\nheredoc: %d\nlimiter: %s\n", exec->nb_cmd, exec->pos_cmd, exec->infile, exec->outfile, exec->cmd, exec->flags[0], exec->flags[1], exec->have_heredoc, exec->limiter);
	//	exec = exec->next;
	//}
	/*if (pipe_len != 1)
	{
		// return_value =
		// return_value = ft_execution_pipe_main(t_envp, cmd, pipe_len);
		// return (return_value);
	}*/


	//clean t_exec
	return (1);
}
