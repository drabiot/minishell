/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:47:37 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/21 00:45:51 by tchartie         ###   ########.fr       */
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
