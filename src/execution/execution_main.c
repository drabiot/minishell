/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:36:16 by nberduck          #+#    #+#             */
/*   Updated: 2024/08/09 16:18:45 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/stat.h>

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

static void	close_err()
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
	else if (WIFSIGNALED(ret))
		ret = WTERMSIG(ret) + 128;
	return (ret);
}

static void set_base_exec(t_exec *current_node, int nb_cmd, int pos_cmd)
{
	current_node->nb_cmd = nb_cmd;
	current_node->pos_cmd = pos_cmd + 1;
	current_node->infile = NULL;
	current_node->outfile[0] = NULL;
	current_node->outfile[1] = NULL;
	current_node->fd_in = -1;
	current_node->fd_out = -1;
	current_node->base_cmd = NULL;
	current_node->cmd = NULL;
	current_node->flags = NULL;
	current_node->have_heredoc = FALSE;
	current_node->limiter = NULL;
	current_node->file_error = FALSE;
	current_node->is_piped = FALSE;
	if (pos_cmd >= 1)
		current_node->is_piped = TRUE;
	current_node->pid = 0;
	current_node->next = NULL;
}

static void	free_paths(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

static char	*get_correct_path(char *cmd, char *content_path, t_bool is_path)
{
	char	**all_path;
	int		i;
	int		access_state;
	char	*correct_path;

	all_path = ft_split((char const *)content_path, ':');
	i = 0;
	access_state = 1;
	if (!all_path || (access(cmd, X_OK) == 0 || is_builtins(cmd) || is_path))
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

static char	*get_cmd(char *arg, t_glob *glob)
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
	if ((arg && access(arg, X_OK) == 0) || (arg && is_builtins(arg)) || is_path)
		tmp_cmd = ft_strdup(arg);
	else if (arg)
		tmp_cmd = ft_strjoin("/", arg); //strdup arg et "/"
	full_path = get_correct_path(tmp_cmd, content_path, is_path);
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
	while (cmd && cmd->type != PIPE)
	{
		if (i == 0)
			line = cmd->arg;
		else if (cmd->type == COMMAND || cmd->type == WORD || cmd->type == PATH)
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

static char	*grab_redir(t_cmd *cmd, t_exec *node, int type, int file, t_glob *glob)
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
			return (cmd->next->arg);
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

static t_exec	*append_node(t_glob *glob, t_cmd *cmd, int nb_cmd, int pos_cmd)
{
	t_exec	*current_node;

	current_node = malloc(sizeof(t_exec));
	if (!current_node)
		return (NULL);
	set_base_exec(current_node, nb_cmd, pos_cmd);
	while (cmd && cmd->type != PIPE)
	{
		if (cmd->type == INPUT || (cmd->next && cmd->next->type == PATH))
			current_node->infile = grab_redir(cmd, current_node, 0, 0, glob);
		else if (cmd->type == TRUNC_REDIR || cmd->type == APPEND_REDIR)
		{
			current_node->outfile[0] = grab_redir(cmd, current_node, 0, 1, glob);
			current_node->outfile[1] = grab_redir(cmd, current_node, 1, 1, glob);
		}
		else if (current_node->cmd == NULL && cmd->type == COMMAND)
		{
			current_node->cmd = get_cmd(cmd->arg, glob);
			current_node->base_cmd = ft_strdup(cmd->arg);
			current_node->flags = get_flags(cmd, current_node->cmd);
		}
		else if (cmd->type == HERE_DOC)
			current_node->have_heredoc = TRUE;
		else if (current_node->limiter == NULL && cmd->type == LIMITER)
			//current_node->limiter = cmd->arg;
			open_heredoc(cmd->arg, current_node);
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
			close_err();
		}
		ft_add_back(&last_node, current_node);
		if (i == 0)
			first_node = last_node;
		i++;
	}
	return(first_node);
}

static void	create_pipe(t_exec *exec)
{
	int		pipe_ret;
	int		fd_pipe[2];
	t_exec	*list;

	list = NULL;
	if (exec)
		list = exec;
	while (exec->next)
	{
		pipe_ret = pipe(fd_pipe);
		if (pipe_ret == -1)
			close_err();
		if (exec->outfile[0] && exec->file_error == FALSE)
		{
			if (ft_strcmp(exec->outfile[1], "append") == 0)
				exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
					| O_APPEND, 0644);
			else if (ft_strcmp(exec->outfile[1], "trunc") == 0)
				exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
			if (exec->fd_out != -1) 
				close(fd_pipe[1]);
		}
		if (exec->fd_out == -1)
			exec->fd_out = fd_pipe[1];
		if (exec->infile && exec->file_error == FALSE)
			exec->fd_in = open(exec->infile, O_RDONLY);
		exec->next->fd_in = fd_pipe[0];
		exec = exec->next; 
	}
	if (exec->outfile[0] && ft_strcmp(exec->outfile[1], "append") == 0 && exec->file_error == FALSE)
		exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
			| O_APPEND, 0644);
	else if (exec->outfile[0] && ft_strcmp(exec->outfile[1], "trunc") == 0 && exec->file_error == FALSE)
		exec->fd_out = open(exec->outfile[0], O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
	if (exec->infile && exec->file_error == FALSE)
	{
		close(exec->fd_in);
		exec->fd_in = open(exec->infile, O_RDONLY);
	}

}

static void	process(t_exec *exec, t_exec *list, t_glob **t_envp)
{
	int		ret_execve;
	int		dup_in;
	int		dup_out;
	struct stat	s_stat;

	dup_in = dup2(exec->fd_in, STDIN_FILENO);
	dup_out = dup2(exec->fd_out, STDOUT_FILENO);
	ret_execve = 0;
	if (!list->base_cmd)
	{
		free_exit(list, *t_envp);
		exit(0);
	}
	if (list->base_cmd[0] == '\0')
	{
		free_exit(list, *t_envp);
		ft_putstr_fd(" command not found\n", 2);
		exit (127);
	}
	if (list->base_cmd[0] == '.' && list->base_cmd[1] == '\0')
	{
		free_exit(list, *t_envp);
		ft_putstr_fd(" filename argument required\n", 2);
		exit(2);
	}
	stat(list->cmd, &s_stat);
	if (dup_in == -1 || dup_out == -1)
		close_err();
	close_fds(list);
	if (exec->file_error == TRUE)
	{
		ret_execve = (*t_envp)->utils->return_code;
		free_exit(list, *t_envp);
		if (exec->nb_cmd >= 2)
			exit (1);
		else
			exit(ret_execve);
	}
	if (is_builtins(exec->cmd))
	{
		ret_execve = ft_find_builtins(STDOUT_FILENO, t_envp, exec);
		free_exit(list, *t_envp);
		exit(ret_execve);
	}
	else if (exec->flags)
		ret_execve = execve(exec->cmd, exec->flags, (*t_envp)->env);
	else
		exit(0);
	if (ret_execve == -1)
	{
		if (ft_strchr(exec->base_cmd, '/')) {
			//ft_errno();
			if (errno == EACCES && (s_stat.st_mode & __S_IFMT) == __S_IFDIR)
			{
				ft_putstr_fd(" Is a directory\n", 2);
				exit (126);
			}
			ft_errno();
			if(errno == EACCES)
				exit(126);
			exit(127);
		}
		//	ft_putstr_fd(" No such file or directory\n", 2);
		else
			ft_putstr_fd(" command not found\n", 2);
		exit(127);
	}
}

static void	init_process(t_exec *list, t_exec *exec, t_glob **t_envp)
{
	exec->pid = fork();
	ft_signal(2);
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

static void	free_t_cmd(t_cmd *cmd)
{
	t_cmd	*next;

	next = NULL;
	while (cmd)
	{
		next = cmd->next;
		free(cmd->arg);
		cmd->arg = NULL;
		free(cmd);
		cmd = next;
	}
}

static void	free_exec(t_exec *exec)
{
	int		i;
	t_exec	*tmp_exec;

	tmp_exec = NULL;
	while (exec)
	{
		i = 0;
		tmp_exec = exec;
		exec = exec->next;
		while (tmp_exec->flags[i])
		{
			free(tmp_exec->flags[i]);
			tmp_exec->flags[i] = NULL;
			i++;
		}
		if (tmp_exec->flags)
			free(tmp_exec->flags);
		tmp_exec->flags = NULL;
		tmp_exec->cmd = NULL;
		if (tmp_exec->base_cmd)
			free(tmp_exec->base_cmd);
		tmp_exec->base_cmd = NULL;
		free(tmp_exec);
		tmp_exec = NULL;
	}
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
	free_t_cmd(cmd);
	// t_exec *tmp = exec;
	// while (tmp)
	// {
	// 	printf("EXEC:\nnb_cmd: %d\npos_cmd: %d\ninfile: %s\noutfile: %s, type: %s\ncmd: %s\nflags: %s %s\nheredoc: %d\nlimiter: %s\nfd_in: %d      fd_out: %d\n", tmp->nb_cmd, tmp->pos_cmd, tmp->infile, tmp->outfile[0], tmp->outfile[1], tmp->cmd, tmp->flags[0], tmp->flags[1], tmp->have_heredoc, tmp->limiter, tmp->fd_in, tmp->fd_out);
	// 	tmp = tmp->next;
	// }
	if (pipe_len == 1 && exec->file_error == TRUE)
		return (1);
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
	// while (tmp)
	// {
	// 	printf("EXEC:\nnb_cmd: %d\npos_cmd: %d\ninfile: %s\noutfile: %s, type: %s\ncmd: %s\nflags: %s %s\nheredoc: %d\nlimiter: %s\nfd_in: %d      fd_out: %d\n", tmp->nb_cmd, tmp->pos_cmd, tmp->infile, tmp->outfile[0], tmp->outfile[1], tmp->cmd, tmp->flags[0], tmp->flags[1], tmp->have_heredoc, tmp->limiter, tmp->fd_in, tmp->fd_out);
	// 	tmp = tmp->next;
	// }
	ret = start_exec(exec, t_envp);
	free_exec(exec);
	//clean t_exec
	return (ret);
}

