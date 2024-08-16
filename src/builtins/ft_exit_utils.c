/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:56:18 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/16 17:58:02 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    free_exit_envp(t_glob *t_envp)
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
		tmp_glob = NULL;
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

