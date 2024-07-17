/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:55:34 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/17 21:56:38 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*static void	create_path(t_cwd *path, t_glob *t_envp)
{
	int	i;
	int	nb_slash;
	char	*first_part;
	char	*last_part;

	while (t_envp->next)
	{
		first_part = ft_strjoin(t_envp->name, "=");
		last_part = ft_strjoin(first_part, t_envp->content);
		if (ft_strncmp(last_part, "PWD=", 4) == 0)
			path->relative_path = last_part + 4;
		free(first_part);
		// free(last_part); // cause of invalid read
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
}*/

void	add_glob_utils(t_glob *t_envp, t_cwd *utils)
{
	t_glob	*cpy;

	cpy = NULL;
	if (t_envp)
		cpy = t_envp;
	while (cpy)
	{
		cpy->utils = utils;
		cpy = cpy->next;
	}
}

int	prompt(t_glob *t_envp)
{
	char		*input;
	char		**arg;

	//create_path(&path, t_envp);
	//printf("\x1b[0;95m%s ", path.absolute_path);
	input = readline("\x1b[0;95muwushell>\x1b[39;49m ");
	if (!input)
		exit (0);
	//free(path.absolute_path);
	// if (!(ft_strncmp(input, "exit", 4)))
	// 	return (0);
	add_history(input);
	arg = lexer(input, t_envp);
	return (1);
}
