/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:55:34 by tchartie          #+#    #+#             */
/*   Updated: 2024/03/29 10:52:10 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	create_path(t_cwd *path, t_list *t_envp)
{
	int	i;
	int	nb_slash;

	while (t_envp->next)
	{
		if (ft_strncmp((char *)t_envp->content, "PWD=", 4) == 0)
			path->relative_path = (char *)t_envp->content + 4;
		t_envp = t_envp->next;
	}
	i = 0;
	nb_slash = 0;
	while (nb_slash < 4)
	{
		if (path->relative_path[i] == '/')
			nb_slash++;
		i++;
	}
	path->absolute_path = ft_strjoin("~/", path->relative_path + i);
}

int	prompt(t_list *t_envp)
{
	char		*input;
	char		**arg;
	t_cwd		path;

	path = (t_cwd){0};
	create_path(&path, t_envp);
	printf("\x1b[0;95m%s ", path.absolute_path);
	input = readline("\x1b[0;95muwushell>\x1b[39;49m ");
	free(path.absolute_path);
	if (!(ft_strncmp(input, "exit", 4)))
		return (0);
	add_history(input);
	arg = lexer(input, t_envp);
	return (1);
}
