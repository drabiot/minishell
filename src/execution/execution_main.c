/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:36:16 by nberduck          #+#    #+#             */
/*   Updated: 2024/08/20 15:29:43 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_fds(t_exec *list)
{
	while (list)
	{
		if (list->fd_in != -1)
			close(list->fd_in);
		list->fd_in = -1;
		if (list->fd_out != -1)
			close(list->fd_out);
		list->fd_out = -1;
		list = list->next;
	}
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

static void	set_base_exec(t_exec *current_node, int nb_cmd, int pos_cmd)
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
	current_node->name_heredoc[0] = NULL;
	current_node->name_heredoc[1] = NULL;
	current_node->name_heredoc[2] = NULL;
	current_node->name_heredoc[3] = NULL;
	current_node->name_heredoc[4] = NULL;
	current_node->name_heredoc[5] = NULL;
	current_node->name_heredoc[6] = NULL;
	current_node->name_heredoc[7] = NULL;
	current_node->name_heredoc[8] = NULL;
	current_node->name_heredoc[9] = NULL;
	current_node->name_heredoc[10] = NULL;
	current_node->name_heredoc[11] = NULL;
	current_node->name_heredoc[12] = NULL;
	current_node->name_heredoc[13] = NULL;
	current_node->name_heredoc[14] = NULL;
	current_node->name_heredoc[15] = NULL;
	current_node->file_error = FALSE;
	current_node->is_piped = FALSE;
	if (pos_cmd >= 1)
		current_node->is_piped = TRUE;
	current_node->pid = 0;
	current_node->next = NULL;
}

void	free_paths(char **path)
{
	int	i;

	i = 0;
	while (path && path[i])
	{
		free(path[i]);
		i++;
	}
	if (path)
		free(path);
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
		{
			if (current_node->infile)
				free(current_node->infile);
			current_node->infile = grab_redir(cmd, current_node, 0, 0, glob);
		}
		else if (cmd->type == TRUNC_REDIR || cmd->type == APPEND_REDIR)
		{
			if (current_node->outfile[0])
				free(current_node->outfile[0]);
			current_node->outfile[0] = grab_redir(cmd, current_node, 0, 1, glob);
			current_node->outfile[1] = grab_redir(cmd, current_node, 1, 1, glob);
		}
		else if (current_node->cmd == NULL && cmd->type == COMMAND)
		{
			current_node->cmd = get_cmd(cmd->arg, glob);
			if (cmd->arg)
				current_node->base_cmd = ft_strdup(cmd->arg);
			current_node->flags = get_flags(cmd, current_node->cmd);
		}
		else if (cmd->type == HERE_DOC)
			current_node->have_heredoc = TRUE;
		else if (cmd->type == LIMITER)
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

static void	check_node(t_cmd *cmd, t_glob *t_envp, t_exec *list, t_exec *nd)
{
	if ((!nd->flags || !nd->cmd) && nd->base_cmd)
	{
		free_t_cmd(cmd);
		free_exit(list, t_envp);
		exit (0);
	}
}

static t_exec	*init_exec(t_cmd *cmd, t_glob *t_envp, int len)
{
	t_exec	*last_node;
	t_exec	*current_node;
	t_exec	*first_node;
	int		i;
	t_cmd	*start;

	last_node = NULL;
	current_node = NULL;
	first_node = NULL;
	start = NULL;
	i = 0;
	if (cmd)
		start = cmd;
	while (i < len)
	{
		current_node = append_node(t_envp, cmd, len, i);
		while (cmd && cmd->type != PIPE)
			cmd = cmd->next;
		while (cmd && cmd->type == PIPE)
			cmd = cmd->next;
		if (!current_node)
			return (NULL);
		ft_add_back(&last_node, current_node);
		if (i == 0)
			first_node = last_node;
		check_node(start, t_envp, first_node, current_node);
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
			return ;
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
		if (exec->fd_in != -1)
			close(exec->fd_in);
		exec->fd_in = open(exec->infile, O_RDONLY);
	}
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

void	free_t_cmd(t_cmd *cmd)
{
	t_cmd	*next;

	next = NULL;
	while (cmd)
	{
		next = cmd->next;
		if (cmd->arg)
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
		while (tmp_exec->flags && tmp_exec->flags[i])
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
		if (tmp_exec->infile)
			free(tmp_exec->infile);
		tmp_exec->infile = NULL;
		if (tmp_exec->outfile[0])
			free(tmp_exec->outfile[0]);
		tmp_exec->outfile[0] = NULL;
		destroy_tmp(&tmp_exec);
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
		return ((*t_envp)->utils->return_code);
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
	{
		free_exec(exec);
		return (1);
	}
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
			free_exec(exec);
			return (ret);
		}
	}
	ret = start_exec(exec, t_envp);
	//close_fds(exec);
	// t_exec *tmp = exec;
	// while (tmp)
	// {
	// 	printf("EXEC:\nnb_cmd: %d\npos_cmd: %d\ninfile: %s\noutfile: %s, type: %s\ncmd: %s\nflags: %s %s\nheredoc: %d\nfd_in: %d      fd_out: %d\n", tmp->nb_cmd, tmp->pos_cmd, tmp->infile, tmp->outfile[0], tmp->outfile[1], tmp->cmd, tmp->flags[0], tmp->flags[1], tmp->have_heredoc, tmp->fd_in, tmp->fd_out);
	// 	tmp = tmp->next;
	// }
	free_exec(exec);
	//clean t_exec
	return (ret);
}

