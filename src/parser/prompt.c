/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:55:34 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/21 20:46:01 by tchartie         ###   ########.fr       */
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

static void	failled_input(t_glob *t_envp)
{
	int	ret;

	ret = t_envp->utils->return_code;
	free_envp(t_envp);
	printf("exit\n");
	exit (ret);
}

int	prompt(t_glob *t_envp)
{
	char		*input;

	ft_signal(1);
	create_env(&t_envp);
	input = readline("\001\033[0;95m\002uwushell> \001\033[0m\002");
	if (t_envp)
		t_envp->utils->failled_here = FALSE;
	if (!input)
		failled_input(t_envp);
	if (g_sig == SIGINT)
	{
		t_envp->utils->return_code = 130;
		g_sig = 0;
	}
	if (input[0] != '\0')
		add_history(input);
	lexer(input, t_envp);
	free_utils(t_envp->utils);
	if (input)
		free (input);
	return (1);
}
