/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_other_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:43:53 by nberduck          #+#    #+#             */
/*   Updated: 2024/06/01 19:52:18 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**ft_get_path(t_glob **t_envp)
{
	char	**return_tab;
	t_glob	*tmp;
	
	tmp = *t_envp;
	while (ft_strcmp(tmp->name, "PATH") != 0)
	{
		if (!tmp)
			return (NULL);
		tmp = tmp->next;
	}
	return_tab = ft_split(tmp->content, ':');
	return (return_tab);
}

static char	**ft_set_argument_argv(t_cmd *cmd, char *path)
{
	char	**return_tab;
	char	*first_part;
	t_cmd	*tmp;
	int		tmp_index;
	int		i;
	
	tmp = ft_lstlast_cmd(cmd);
	tmp_index = (int)tmp->index;
	printf("%i.\n", tmp_index);
	return_tab = (char **)malloc((tmp_index + 2) * sizeof (char *));
	if (!return_tab)
		return (NULL);
	first_part = ft_strjoin(path, "/");
	return_tab[0] = ft_strjoin(first_part, cmd->arg);
	free(first_part);
	i = 1;
	tmp = cmd->next;
	while (i != tmp_index + 1)
	{
		if (tmp && tmp->arg)
		{
			return_tab[i] = ft_substr(tmp->arg, 0, ft_strlen(tmp->arg));
			tmp = tmp->next;
		}
		else
		{
			printf("t\n");
			return_tab[i] = NULL;
			return(return_tab);
		}
		i++;
	}
	return_tab[i] = NULL;
	return (return_tab);
}

static char	***ft_set_argv(t_cmd *cmd, char **paths)
{
	char	***return_tab;
	char	*path;
	int		i;
	int		len;
	
	len = ft_tab_len(paths);
	return_tab = (char ***)malloc((len + 1) * sizeof(char **));
	if (!return_tab)
		return (NULL);
	i = 0;
	while (i != len)
	{
		path = paths[i];
		return_tab[i] = ft_set_argument_argv(cmd, path);
		if (!return_tab[i])
			return (NULL); // Have to clear tab here
		i++;
	}
	return_tab[i] = NULL;
	return (return_tab);
}

static char	**ft_set_char_envp(t_glob **t_envp)
{
	char	**return_tab;
	char	*first_part;
	t_glob	*tmp;
	int		i;
	
	return_tab = (char **)malloc((ft_glob_len(*t_envp) + 1) * sizeof(char *));
	tmp = *t_envp;
	i = 0;
	while (tmp)
	{
		if (tmp->equal == 1)
		{
			first_part = ft_strjoin(tmp->name, "=");
			return_tab[i] = ft_strjoin(first_part, tmp->content);
			free(first_part);
			if (!return_tab[i])
				return(NULL);// Have to clear here
		}
		tmp = tmp->next;
		i++;
	}
	return_tab[i] = NULL;
	return (return_tab);
}

static	int ft_execute_cmd(int fd, char **paths, char **envp, char ***argvs)
{
	int	return_value;
	int	i;

	return_value = -1;
	i = 0;
	(void)fd;
	while (return_value != 0 && paths[i])
	{
		return_value = access(argvs[i][0], X_OK);
		if (return_value != 0)
			i++;
	}
	if (!paths[i])
		return (1);
	execve(argvs[i][0], argvs[i], envp);
	// printf("fqffg%i\n", return_value);
	return (return_value);
}
int	ft_execute_other_cmd(int fd, t_glob **t_envp, t_cmd *cmd)
{
	char	**paths;
	char	**envp;
	char	***argvs;
	int	i;
	// int	j;	
	(void)fd;
	paths = ft_get_path(t_envp);
	envp = ft_set_char_envp(t_envp);
	argvs = ft_set_argv(cmd, paths);

	i = 0;
	// while (paths[i])
	// {
	// 	printf("path[%i]:%s.\n", i, paths[i]);
	// 	i++;
	// }
	// i = 0;
	// while(envp[i])
	// {
	// 	printf("envp[%i]:%s.\n", i, envp[i]);
	// 	i++;
	// }
	// i = 0;
	// while (argvs[i])
	// {
	// 	j = 0;
	// 	while (argvs[i][j])
	// 	{
	// 		printf("argv[%i],arg[%i]:%s.\n", i, j, argvs[i][j]);
	// 		j++;
	// 	}
	// 	i++;
	// }
	ft_execute_cmd(fd, paths, envp, argvs);
	ft_clear_tab(paths);
	ft_clear_tab(envp);
	ft_clear_argvs(argvs);
	return (0);
}
