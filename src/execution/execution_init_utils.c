/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_init_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:21:29 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/20 17:22:58 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_infile(t_cmd *cmd, t_exec *current_node, t_glob *glob)
{
	if (current_node->infile)
		free(current_node->infile);
	current_node->infile = grab_redir(cmd, current_node, 0, 0, glob);
}

void	set_outfile(t_cmd *cmd, t_exec *current_node, t_glob *glob)
{
	if (current_node->outfile[0])
		free(current_node->outfile[0]);
	current_node->outfile[0] = grab_redir(cmd, current_node, 0, 1, glob);
	current_node->outfile[1] = grab_redir(cmd, current_node, 1, 1, glob);
}

void	set_cmds(t_cmd *cmd, t_exec *current_node, t_glob *glob)
{
	current_node->cmd = get_cmd(cmd->arg, glob);
	if (cmd->arg)
		current_node->base_cmd = ft_strdup(cmd->arg);
	current_node->flags = get_flags(cmd, current_node->cmd);
}
