/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:47:37 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/20 19:05:20 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	start_exec(t_exec *exec, t_glob **t_envp)
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
