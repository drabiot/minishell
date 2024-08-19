/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:56:18 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/19 21:06:29 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	calculate_exit_code(int exit_code)
{
	if (exit_code >= 256)
		return (exit_code % 256);
	if (exit_code < 0)
		return (256 - (-exit_code % 256));
	return (exit_code);
}

t_bool	check_limits(const char *num, const char *limit, int i, int j)
{
	int		diff;
	t_bool	is_out;

	is_out = FALSE;
	while (num[i + j] && !is_out)
	{
		diff = num[i + j] - limit[i];
		if (diff < 0)
			is_out = TRUE;
		i++;
	}
	return (diff > 0);
}

void	free_utils(t_cwd *utils)
{
	int		i;
	t_cwd	*tmp;

	i = 0;
	if (!utils)
		return ;
	tmp = utils;
	while (tmp->env && tmp->env[i])
	{
		free(tmp->env[i]);
		tmp->env[i] = NULL;
		i++;
	}
	if (tmp->env)
		free(tmp->env);
	tmp->env = NULL;
}

void	free_exit_envp(t_glob *t_envp)
{
	t_glob	*tmp_glob;

	tmp_glob = NULL;
	free_utils(t_envp->utils);
	while (t_envp)
	{
		tmp_glob = t_envp;
		t_envp = t_envp->next;
		if (tmp_glob->name)
			free(tmp_glob->name);
		if (tmp_glob->content)
			free(tmp_glob->content);
		free(tmp_glob);
		tmp_glob = (NULL);
	}
}

void	free_exit_tmp_exec(t_exec *tmp_exec)
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
	free_tmp(&tmp_exec);
	free(tmp_exec);
	tmp_exec = NULL;
}