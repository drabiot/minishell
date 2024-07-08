/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:52:46 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/05 12:48:45 by adorlac          ###   ########.fr       */
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
