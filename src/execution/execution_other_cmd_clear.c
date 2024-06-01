/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_other_cmd_clear.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:54:27 by nberduck          #+#    #+#             */
/*   Updated: 2024/06/01 19:02:16 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_clear_tab(char **tmp)
{
	int	i;
	
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

void	ft_clear_argvs(char ***argvs)
{
	int	i;
	int	j;

	i = 0;
	while (argvs[i])
	{
		j = 0;
		while (argvs[i][j])
		{
			free(argvs[i][j]);
			j++;
		}
		free(argvs[i]);
		i++;
	}
	free(argvs);
}