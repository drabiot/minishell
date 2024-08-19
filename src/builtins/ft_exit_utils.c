/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:56:18 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/19 18:03:49 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_exit_error(int fd, t_glob *t_envp, t_exec *exec, int *exit_code)
{
	ft_putstr_fd("exit\n", fd);
	free_exit(exec, t_envp);
	exit(*exit_code);
}

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

void	free_exit_envp(t_glob *t_envp)
{
	t_glob	*tmp_glob;

	tmp_glob = NULL;
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
