/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:41:30 by nberduck          #+#    #+#             */
/*   Updated: 2024/08/20 15:57:09 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_errno(void)
{
	char	*error;

	error = strerror(errno);
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

void	free_t_cmd(t_cmd *cmd)
{
	t_cmd	*next;

	next = NULL;
	while (cmd)
	{
		next = cmd->next;
		if (cmd->arg)
			free(cmd->arg);
		cmd->arg = NULL;
		free(cmd);
		cmd = next;
	}
}

static void	free_inside_exec(t_exec *tmp_exec)
{
	if (tmp_exec->flags)
		free(tmp_exec->flags);
	tmp_exec->flags = NULL;
	tmp_exec->cmd = NULL;
	if (tmp_exec->base_cmd)
		free(tmp_exec->base_cmd);
	tmp_exec->base_cmd = NULL;
	if (tmp_exec->infile)
		free(tmp_exec->infile);
	tmp_exec->infile = NULL;
	if (tmp_exec->outfile[0])
		free(tmp_exec->outfile[0]);
	tmp_exec->outfile[0] = NULL;
}

void	free_exec(t_exec *exec)
{
	int		i;
	t_exec	*tmp_exec;

	tmp_exec = NULL;
	while (exec)
	{
		i = 0;
		tmp_exec = exec;
		exec = exec->next;
		while (tmp_exec->flags && tmp_exec->flags[i])
		{
			free(tmp_exec->flags[i]);
			tmp_exec->flags[i] = NULL;
			i++;
		}
		free_inside_exec(tmp_exec);
		destroy_tmp(&tmp_exec);
		free(tmp_exec);
		tmp_exec = NULL;
	}
}

void	free_paths(char **path)
{
	int	i;

	i = 0;
	while (path && path[i])
	{
		free(path[i]);
		i++;
	}
	if (path)
		free(path);
}
