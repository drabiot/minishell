/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:10:46 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/15 19:30:14 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_glob_len(t_glob *tmp)
{
	int	len;

	len = 0;
	while (tmp)
	{
		if (tmp->equal == 1)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

int	ft_tab_len(char	**tab)
{
	char	**tmp;
	int		i;

	tmp = tab;
	i = 0;
	while (tmp[i])
		i++;
	return (i);
}

int	ft_pipe_len(t_cmd *cmd)
{
	unsigned int	len;

	len = 1;
	while (cmd)
	{
		if (cmd->type == PIPE)
			len++;
		cmd = cmd->next;
	}
	return (len);
}

int	ft_have_heredoc(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->type == HERE_DOC)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

void	destroy_tmp(t_exec **exec)
{
	int	i;

	i = 0;
	if (!*exec)
		return ;
	while (i < 16)
	{
		if ((*exec)->name_heredoc[i])
		{
			unlink((*exec)->name_heredoc[i]);
			free((*exec)->name_heredoc[i]);
		}
		(*exec)->name_heredoc[i] = NULL;
		i++;
	}
}

void	free_tmp(t_exec **exec)
{
	int	i;

	i = 0;
	if (!*exec)
		return ;
	while (i < 16)
	{
		if ((*exec)->name_heredoc[i])
			free((*exec)->name_heredoc[i]);
		(*exec)->name_heredoc[i] = NULL;
		i++;
	}
}
