/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:55:34 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/09 17:18:34 by adorlac          ###   ########.fr       */
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
	int			ret;

	// rl_outstream = stdin;
	//create_path(&path, t_envp);
	//printf("\x1b[0;95m%s ", path.absolute_path);
	//input = readline("uwushell> ");
	ft_signal(1);
	ret = 0;
	input = readline("\001\033[0;95m\002uwushell> \001\033[0m\002");
	if (!input)
	{
		ret = t_envp->utils->return_code;
		free_envp(t_envp);
		printf("exit\n");
		exit (ret);
	}
	//free(path.absolute_path);
	// if (!(ft_strncmp(input, "exit", 4)))
	// 	return (0);
	add_history(input);
	arg = lexer(input, t_envp);
	return (1);
}
