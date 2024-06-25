/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:11:06 by nberduck          #+#    #+#             */
/*   Updated: 2024/06/25 11:47:55 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_create_file_redir(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT, 0777);
	if (!fd)
		return (1);
	return (fd);
}

static void ft_clear_redir(t_cmd **cmd)
{
	t_cmd	*tmp;
	
	tmp = *cmd;
	while (tmp && tmp->next)
	{
		if (tmp->next->type == TRUNC_REDIR || tmp->next->type == APPEND_REDIR)
		{
			tmp->next = NULL;
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

static t_cmd *ft_find_name(t_cmd *cmd)
{
	t_cmd *tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == TRUNC_REDIR || tmp->type == APPEND_REDIR)
			return (tmp->next);
		tmp = tmp->next;
	}
	return (NULL);
}

static char *ft_get_file_content(char *name)
{
	int		fd;
	char	*start;
	char	*line;
	char	*tmp;
	
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	start = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (start)
			tmp = ft_strjoin(start, line);
		else
			tmp = line;
		if (start)
			free(start);
		free(line);
		start = tmp;
		free(tmp);
		line = get_next_line(fd);
	}
	close(fd);
	return (tmp);
}
int	ft_append_redir(t_glob **t_envp, t_cmd *cmd)
{
	int		fd;
	t_cmd	*name;
	char	*file_content;
	
	if(!cmd->next || !cmd->next->next)
		return (1);
	name = ft_find_name(cmd);
	file_content = ft_get_file_content(name->arg);
	fd = ft_create_file_redir(name->arg);
	if (fd == -1)
		return (1);
	ft_clear_redir(&cmd);
	ft_putstr_fd(file_content, fd);
	// free(file_content);
	// printf("%s,%s.\n", cmd->arg, cmd->next->arg);
	ft_execution_cmd(fd, t_envp, cmd);
	close(fd);
	return (0);
}

int	ft_trunc_redir(t_glob **t_envp, t_cmd *cmd)
{
	int		fd;
	t_cmd	*name;
	
	if(!cmd->next || !cmd->next->next)
		return (1);
	name = ft_find_name(cmd);
	unlink(name->arg);
	fd = ft_create_file_redir(name->arg);
	if (fd == -1)
		return (1);
	ft_clear_redir(&cmd);
	// printf("%s,%s.\n", cmd->arg, cmd->next->arg);
	ft_execution_cmd(fd, t_envp, cmd);
	close(fd);
	return (0);
}

static void ft_clear_input_redir(t_cmd **cmd)
{
	t_cmd	*tmp;
	
	tmp = *cmd;
	while (tmp && tmp->next)
	{
		if (tmp->next->type == INPUT)
		{
				tmp->next = tmp->next->next;
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

int ft_input_redir(t_glob **t_envp, t_cmd *cmd)
{
	if(!cmd->next || !cmd->next->next)
		return (1);
	t_cmd	*tmp;

	tmp = cmd;
	// while (tmp)
	// {
	// 	printf("%s\n", tmp->arg);
	// 	tmp = tmp->next;
	// }
	ft_clear_input_redir(&cmd);
	tmp = cmd;
	while (tmp)
	{
		printf("%s\n", tmp->arg);
		tmp = tmp->next;
	}
	ft_execute_other_cmd(t_envp, cmd);
	return (0);
}
