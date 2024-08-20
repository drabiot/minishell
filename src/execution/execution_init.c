/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:35:40 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/20 16:38:29 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	set_here_exec(t_exec *current_node)
{
	current_node->have_heredoc = FALSE;
	current_node->name_heredoc[0] = NULL;
	current_node->name_heredoc[1] = NULL;
	current_node->name_heredoc[2] = NULL;
	current_node->name_heredoc[3] = NULL;
	current_node->name_heredoc[4] = NULL;
	current_node->name_heredoc[5] = NULL;
	current_node->name_heredoc[6] = NULL;
	current_node->name_heredoc[7] = NULL;
	current_node->name_heredoc[8] = NULL;
	current_node->name_heredoc[9] = NULL;
	current_node->name_heredoc[10] = NULL;
	current_node->name_heredoc[11] = NULL;
	current_node->name_heredoc[12] = NULL;
	current_node->name_heredoc[13] = NULL;
	current_node->name_heredoc[14] = NULL;
	current_node->name_heredoc[15] = NULL;
}

void	set_base_exec(t_exec *current_node, int nb_cmd, int pos_cmd)
{
	current_node->nb_cmd = nb_cmd;
	current_node->pos_cmd = pos_cmd + 1;
	current_node->infile = NULL;
	current_node->outfile[0] = NULL;
	current_node->outfile[1] = NULL;
	current_node->fd_in = -1;
	current_node->fd_out = -1;
	current_node->base_cmd = NULL;
	current_node->cmd = NULL;
	current_node->flags = NULL;
	set_here_exec(current_node);
	current_node->file_error = FALSE;
	current_node->is_piped = FALSE;
	if (pos_cmd >= 1)
		current_node->is_piped = TRUE;
	current_node->pid = 0;
	current_node->next = NULL;
}

t_exec	*init_exec(t_cmd *cmd, t_glob *t_envp, int len)
{
	t_exec	*last_node;
	t_exec	*current_node;
	t_exec	*first_node;
	int		i;
	t_cmd	*start;

	last_node = NULL;
	current_node = NULL;
	first_node = NULL;
	start = NULL;
	i = 0;
	if (cmd)
		start = cmd;
	while (i < len)
	{
		current_node = append_node(t_envp, cmd, len, i);
		while (cmd && cmd->type != PIPE)
			cmd = cmd->next;
		while (cmd && cmd->type == PIPE)
			cmd = cmd->next;
		if (!current_node)
			return (NULL);
		ft_add_back(&last_node, current_node);
		if (i == 0)
			first_node = last_node;
		check_node(start, t_envp, first_node, current_node);
		i++;
	}
	return (first_node);
}

t_exec	*append_node(t_glob *glob, t_cmd *cmd, int nb_cmd, int pos_cmd)
{
	t_exec	*current_node;

	current_node = malloc(sizeof(t_exec));
	if (!current_node)
		return (NULL);
	set_base_exec(current_node, nb_cmd, pos_cmd);
	while (cmd && cmd->type != PIPE)
	{
		if (cmd->type == INPUT || (cmd->next && cmd->next->type == PATH))
		{
			if (current_node->infile)
				free(current_node->infile);
			current_node->infile = grab_redir(cmd, current_node, 0, 0, glob);
		}
		else if (cmd->type == TRUNC_REDIR || cmd->type == APPEND_REDIR)
		{
			if (current_node->outfile[0])
				free(current_node->outfile[0]);
			current_node->outfile[0] = grab_redir(cmd, current_node, 0, 1, glob);
			current_node->outfile[1] = grab_redir(cmd, current_node, 1, 1, glob);
		}
		else if (current_node->cmd == NULL && cmd->type == COMMAND)
		{
			current_node->cmd = get_cmd(cmd->arg, glob);
			if (cmd->arg)
				current_node->base_cmd = ft_strdup(cmd->arg);
			current_node->flags = get_flags(cmd, current_node->cmd);
		}
		else if (cmd->type == HERE_DOC)
			current_node->have_heredoc = TRUE;
		else if (cmd->type == LIMITER)
			open_heredoc(cmd->arg, current_node);
		cmd = cmd->next;
	}
	return (current_node);
}
