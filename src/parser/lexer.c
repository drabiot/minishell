/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:52:46 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/21 20:46:10 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	lexer(char *input, t_glob *t_envp)
{
	t_input	cmd;

	cmd = (t_input){0};
	cmd.str = input;
	cmd.i = 0;
	tokenizer(&cmd, t_envp, 0);
}
