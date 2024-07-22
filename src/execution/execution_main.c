/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:36:16 by nberduck          #+#    #+#             */
/*   Updated: 2024/07/22 14:17:58 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	close_fds(t_exec *list)
{
	while (list)
	{
		if (list->fd_in != -1)
			close(list->fd_in);
		if (list->fd_out != -1)
			close(list->fd_out);
		list = list->next;
	}
}

static void	close_err(void)
{
	return ;
}

static int	wait_all_pid(t_exec *list)
{
	int	ret;

	ret = 0;
	while (list->next)
	{
		waitpid(list->pid, NULL, 0);
		list = list->next;
	}
	waitpid(list->pid, &ret, 0);
	if (WIFEXITED(ret))
		ret = WEXITSTATUS(ret);
	return (ret);
}

static void	set_base_exec(t_exec *current_node, int nb_cmd, int pos_cmd)
{
	current_node->nb_cmd = nb_cmd;
	current_node->pos_cmd = pos_cmd + 1;
	current_node->infile = NULL;
	current_node->outfile[0] = NULL;
	current_node->outfile[1] = NULL;
	current_node->fd_in = -1;
	current_node->fd_out = -1;
	current_node->cmd = NULL;
	current_node->flags = NULL;
	current_node->have_heredoc = TRUE;
	current_node->limiter = NULL;
	current_node->is_piped = FALSE;
	if (pos_cmd >= 1)
		current_node->is_piped = TRUE;
	current_node->pid = 0;
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
	if (!all_path || (access(cmd, X_OK) == 0 || is_builtins(cmd)))
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
	content_path = NULL;
	tmp_cmd = NULL;
	if (glob)
		path = glob;
	while (path && ft_strcmp(path->name, "PATH") != 0)
		path = path->next;
	if (path)
		content_path = path->content;
	if ((arg && access(arg, X_OK) == 0) || (arg && is_builtins(arg)))
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
			line = ft_strjoin(ft_strdup(line), ft_strdup("\b"));
			line = ft_strjoin(ft_strdup(line), ft_strdup(cmd->arg));
		}
		i++;
		cmd = cmd->next;
	}
	flags = ft_split(line, '\b');
	if (!flags || !*flags)
		return (NULL);
	free(flags[0]);
	flags[0] = path;
	return (flags);
}

static char	*grab_redir(t_cmd *cmd, int type)
{
	if (type == 0)
	{
		if (!cmd && !cmd->next)
			return (NULL);
		return (cmd->next->arg);
	}
	else if (type == 1)
	{
		if (cmd->type == APPEND_REDIR)
			return ("append");
		else if (cmd->type == TRUNC_REDIR)
			return ("trunc");
		else
			return (NULL);
	}
	else
		return (NULL);
	//open files
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
		if (cmd->type == INPUT)
			current_node->infile = grab_redir(cmd, 0);
		else if (cmd->type == TRUNC_REDIR || cmd->type == APPEND_REDIR)
		{
			current_node->outfile[0] = grab_redir(cmd, 0);
			current_node->outfile[1] = grab_redir(cmd, 1);
		}
		else if (current_node->cmd == NULL && cmd->type == COMMAND)
		{
			current_node->cmd = get_cmd(cmd->arg, glob);
			current_node->flags = get_flags(cmd, current_node->cmd);
		}
		else if (cmd->type == HERE_DOC)
			current_node->have_heredoc = TRUE;
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
	t_exec	*buffer;

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
			close_err();
		}
		ft_add_back(&last_node, current_node);
		if (i == 0)
			first_node = last_node;
		i++;
	}
	return (first_node);
}

static void	create_pipe(t_exec *exec)
{
	int		i;
	int		pipe_ret;
	int		fd_pipe[2];
	t_exec	*list;

	i = 0;
	list = NULL;
	if (exec)
		list = exec;
	while (exec->next)
	{
		pipe_ret = pipe(fd_pipe);
		if (pipe_ret == -1)
			close_err();
		if (exec->outfile[0])
		{
			if (ft_strcmp(exec->outfile[1], "append") == 0)
				exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
						| O_APPEND, 0644);
			else if (ft_strcmp(exec->outfile[1], "trunc") == 0)
				exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
						| O_TRUNC, 0644);
			close(fd_pipe[1]);
		}
		else
			exec->fd_out = fd_pipe[1];
		if (exec->infile)
		{
			exec->fd_in = open(exec->infile, O_RDONLY);
			close(fd_pipe[0]);
		}
		else
			exec->next->fd_in = fd_pipe[0];
		exec = exec->next;
	}
	if (exec->outfile[0] && ft_strcmp(exec->outfile[1], "append") == 0)
		exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
				| O_APPEND, 0644);
	else if (exec->outfile[0] && ft_strcmp(exec->outfile[1], "trunc") == 0)
		exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
}

static void	process(t_exec *exec, t_exec *list, t_glob **t_envp)
{
	int	ret_execve;
	int	dup_in;
	int	dup_out;

	dup_in = dup2(exec->fd_in, STDIN_FILENO);
	dup_out = dup2(exec->fd_out, STDOUT_FILENO);
	ret_execve = 0;
	if (dup_in == -1 || dup_out == -1)
		close_err();
	close_fds(list);
	if (is_builtins(exec->cmd))
	{
		ret_execve = ft_find_builtins(STDOUT_FILENO, t_envp, exec);
		//free all memory allocated to child process
		exit(ret_execve);
	}
	else if (exec->flags)
		ret_execve = execve(exec->cmd, exec->flags, (*t_envp)->env);
	else
		exit(0);
	if (ret_execve == -1)
	{
		ft_putstr_fd(" command not found\n", 2);
		exit(127);
	}
}

static void	init_process(t_exec *list, t_exec *exec, t_glob **t_envp)
{
	exec->pid = fork();
	if (exec->pid == -1)
		close_err();
	else if (exec->pid == 0)
		process(exec, list, t_envp);
}

static int	start_exec(t_exec *exec, t_glob **t_envp)
{
	int		ret;
	t_exec	*list;

	ret = 0;
	list = NULL;
	create_pipe(exec);
	if (exec)
		list = exec;
	while (exec)
	{
		init_process(list, exec, t_envp);
		exec = exec->next;
	}
	close_fds(list);
	ret = wait_all_pid(list);
	return (ret);
}

int	ft_execution_main(t_glob **t_envp, t_cmd *cmd)
{
	int		pipe_len;
	t_exec	*exec;
	int		ret;

	if (!cmd)
		return (0);
	pipe_len = ft_pipe_len(cmd);
	exec = init_exec(cmd, *t_envp, pipe_len);
	ret = 0;
	if (pipe_len == 1 && is_builtins(exec->cmd))
	{
		if (exec->outfile[0] && ft_strcmp(exec->outfile[1], "append") == 0)
			exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		else if (exec->outfile[0] && ft_strcmp(exec->outfile[1], "trunc") == 0)
			exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
		else
			exec->fd_out = 1;
		ret = ft_find_builtins(exec->fd_out, t_envp, exec);
		if (ret != -1)
		{
			if (exec->fd_out == 1)
				exec->fd_out = -1;
			close_fds(exec);
			return (ret);
		}
	}
	// t_exec *tmp = exec;
	ret = start_exec(exec, t_envp);
	// while (tmp)
	// {
	// 	printf("EXEC:\nnb_cmd: %d\npos_cmd: %d\ninfile: %s\noutfile: %s, type: %s\ncmd: %s\nflags: %s %s\nheredoc: %d\nlimiter: %s\nfd_in: %d      fd_out: %d\n", tmp->nb_cmd, tmp->pos_cmd, tmp->infile, tmp->outfile[0], tmp->outfile[1], tmp->cmd, tmp->flags[0], tmp->flags[1], tmp->have_heredoc, tmp->limiter, tmp->fd_in, tmp->fd_out);
	// 	tmp = tmp->next;
	// }
	//clean t_exec
	return (ret);
}