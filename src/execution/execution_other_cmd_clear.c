/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_other_cmd_clear.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:54:27 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/09 15:04:50 by adorlac          ###   ########.fr       */
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
