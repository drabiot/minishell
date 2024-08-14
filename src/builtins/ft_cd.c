/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:27:33 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/14 14:27:44 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	refresh_pwd(t_glob ***t_envp)
{
	t_glob	*start;
	t_glob	*old_pwd;
	t_glob	*end;
	char	*content_pwd;
	char	*path;

	start = NULL;
	old_pwd = NULL;
	end = NULL;
	path = getcwd(NULL, 0);
	if (!path)
		return ;
	(**t_envp)->content = path;
	content_pwd = (**t_envp)->content;
	if (**t_envp)
		start = **t_envp;
	while (start)
	{
		if (ft_strcmp(start->name, "PWD") == 0)
		{
			content_pwd = start->content;
			start->content = path;
		}
		if (ft_strcmp(start->name, "OLDPWD") == 0)
			old_pwd = start;
		end = start;
		start = start->next;
	}
	/*if (!old_pwd) //redo if end doesn't exist & mke it work when no PWD
	{
		old_pwd = malloc(sizeof(t_glob));
		if (!old_pwd)
			exit (1); //free leak
		old_pwd->name = "OLDPWD";
		old_pwd->content = content_pwd;
		old_pwd->env = end->env; //do it
		old_pwd->equal = 1;
		old_pwd->utils = end->utils;
		old_pwd->next = NULL;
		end->next = old_pwd;
	}*/
	old_pwd->content = content_pwd;
}

int	ft_cd(t_exec *exec, t_glob **t_envp)
{
	char	*path_start;
	char	*path_join_half;
	char	*path_join;
	char	*path;

	path_start = NULL;
	path_join_half = NULL;
	path_join = NULL;
	path = NULL;
	if (!exec->flags[1])
	{
		path = getenv("HOME");
		if (!path)
			ft_putstr_fd(" Error: HOME environment variable not found\n", 2);
		else if (path && chdir(path) != 0)
			ft_putstr_fd(" Error: Can't change directory\n", 2);
		return (0);
	}
	if (exec->flags[2])
	{
		ft_putstr_fd(" too many arguments\n", 2);
		return (1);
	}
	path = exec->flags[1];
	if (path[0] == '/')
	{
		if (chdir(path) == -1)
		{
			ft_putstr_fd(" No such file or directory\n", 2);
			return (1);
		}
		refresh_pwd(&t_envp);
		return (0);
	}
	path_start = getcwd(NULL, 0);
	if (path_start)
	{
		path_join_half = ft_strjoin(path_start, "/");
		path_join = ft_strjoin(path_join_half, path);
	}
	else
		path_join = ft_strdup(path);
	if (chdir(path_join) == -1)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		return (1);
	}
	refresh_pwd(&t_envp);
	free(path_join);
	free(path_start);
	free(path_join_half);
	return (0);
}
