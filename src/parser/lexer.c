/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:52:46 by tchartie          #+#    #+#             */
/*   Updated: 2024/03/28 23:54:14 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**lexer(char *input, t_list *t_envp)
{
	t_input	cmd;

	cmd = (t_input){0};
	cmd.str = input;
	cmd.i = 0;
	tokenizer(&cmd, t_envp);
	return (NULL);
}
