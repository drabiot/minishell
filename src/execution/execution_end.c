/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:45:48 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/21 04:42:27 by tchartie         ###   ########.fr       */
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

int	wait_all_pid(t_exec *list)
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
	if (ret == 131)
	{
		ft_putstr_fd("Quit\n", 2);
	}
	return (ret);
}
