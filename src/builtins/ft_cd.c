/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:27:33 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/18 22:22:50 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cd(t_exec *exec, t_glob **t_envp)
{
	char	*path_start;
	char	*path_join_half;
	char	*path_join;
	char	*path;

	if (exec->flags[2])
	{
		ft_putstr_fd(" too many arguments\n", 2);
		(*t_envp)->utils->return_code = 1;
		return (1);
	}
	path = exec->flags[1];
	if (path[0] == '/')
	{
		if (chdir(path) == -1)
		{
			ft_putstr_fd(" No such file or directory\n", 2);
			(*t_envp)->utils->return_code = 1;
			return (1);
		}
		return (0);
	}
	path_start = getcwd(NULL, 0);
	path_join_half = ft_strjoin(path_start, "/");
	path_join = ft_strjoin(path_join_half, path);
	if (chdir(path_join) == -1)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		(*t_envp)->utils->return_code = 1;
		return (1);
	}
	free(path_join);
	free(path_start);
	free(path_join_half);
	return (0);
}
