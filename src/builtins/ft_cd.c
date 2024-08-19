/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:27:33 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/19 22:40:31 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fresh_pwd(t_glob ***t_envp, t_glob *start, t_glob *old_pwd, t_glob *end)
{
	char	*content_pwd;
	char	*path;

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
	old_pwd->content = content_pwd;
}

int	change_directory(char *path, t_glob **t_envp)
{
	if (!path)
	{
		ft_putstr_fd(" Error: HOME environment variable not found\n", 2);
		return (1);
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		return (1);
	}
	fresh_pwd(&t_envp, NULL, NULL, NULL);
	return (0);
}

char	*construct_path(char *path)
{
	char	*cwd;
	char	*full_path;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	full_path = NULL;
	if (cwd)
	{
		tmp = ft_strjoin(cwd, "/");
		full_path = ft_strjoin(tmp, path);
		free(tmp);
		free(cwd);
	}
	else
		full_path = ft_strdup(path);
	return (full_path);
}

int	ft_cd(t_exec *exec, t_glob **t_envp)
{
	char	*path;
	char	*full_path;
	int		result;

	if (!exec->flags[1])
		return (change_directory(getenv("HOME"), t_envp));
	if (exec->flags[2])
	{
		ft_putstr_fd(" too many arguments\n", 2);
		return (1);
	}
	path = exec->flags[1];
	if (path[0] == '/')
		return (change_directory(path, t_envp));
	full_path = construct_path(path);
	result = change_directory(full_path, t_envp);
	free(full_path);
	return (result);
}
