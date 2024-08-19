/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:55:34 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/19 18:25:37 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	create_env(&t_envp);
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
