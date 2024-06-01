/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:27:33 by nberduck          #+#    #+#             */
/*   Updated: 2024/05/30 05:22:06 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cd(t_cmd *cmd)
{
	char	*path_start;
	char	*path_join_half;
	char	*path_join;
	char	*path;

	path = cmd->arg;
	if (path[0] == '/')
	{
		if (chdir(path) == -1)
			return (1);
		return (0);
	}
	path_start = ft_pwd();
	path_join_half = ft_strjoin(path_start, "/");
	path_join = ft_strjoin(path_join_half, path);
	if (chdir(path_join) == -1)
		return (1);
	free(path_join);
	free(path_start);
	free(path_join_half);
	return (0);
}
