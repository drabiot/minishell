/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:55:34 by tchartie          #+#    #+#             */
/*   Updated: 2024/03/28 23:53:51 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	prompt(t_list *t_envp)
{
	char	*input;
	char	**arg;

	input = readline("\x1b[0;95muwushell>\x1b[39;49m ");
	if (!(ft_strncmp(input, "exit", 4)))
		return (0);
	add_history(input);
	arg = lexer(input, t_envp);
	return (1);
}
