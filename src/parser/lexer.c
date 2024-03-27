/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:52:46 by tchartie          #+#    #+#             */
/*   Updated: 2024/03/26 16:57:05 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/libft.h"

char	**lexer(char *input)
{
	t_input	cmd;

	cmd = (t_input){0};
	cmd.str = input;
	cmd.i = 0;
	tokenizer(&cmd);
	return (NULL);
}
