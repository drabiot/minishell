/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:27:33 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/05 12:58:03 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cd(char *path)
{
	char	*path_start;
	char	*path_join_half;
	char	*path_join;

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
