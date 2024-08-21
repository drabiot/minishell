/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:47:37 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/21 03:16:44 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	start_exec(t_exec *exec, t_glob **t_envp)
{
	int		ret;
	t_exec	*list;

	ret = 0;
	list = NULL;
	if (exec)
		list = exec;
	while (exec)
	{
		create_pipe(exec);
		init_process(list, exec, t_envp);
		close(exec->fd_in);
		close(exec->fd_out);
		exec = exec->next;
	}
	close_fds(list);
	ret = wait_all_pid(list);
	return (ret);
}

int	return_error(t_glob **t_envp, t_exec *exec, int pipe_len)
{
	if (*t_envp && (*t_envp)->utils->failled_here == TRUE)
	{
		free_exec(exec);
		return (130);
	}
	if (pipe_len == 1 && exec->file_error == TRUE)
	{
		free_exec(exec);
		return (1);
	}
	else
		return (0);
}

t_bool	check_sign(t_glob *t_envp, int fd, char *finish_line)
{
	if (g_sig == SIGINT && t_envp)
	{
		t_envp->utils->failled_here = TRUE;
		close(fd);
		free(finish_line);
		return (TRUE);
	}
	return (FALSE);
}
