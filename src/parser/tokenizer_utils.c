/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:23:01 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/19 22:56:10 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	is_white_space(char *str, int i)
{
	if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		return (1);
	return (0);
}

t_bool	is_special_char(char *str, int i)
{
	if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		return (1);
	return (0);
}

t_bool	is_redirection(t_input *cmd, t_token *token)
{
	char	c;

	c = cmd->str[cmd->i];
	if (!(c == '>' || c == '<' || c == '|'))
		return (0);
	if ((c == '>' || c == '<') && c == cmd->str[cmd->i + 1])
		cmd->i++;
	token->end = cmd->i;
	return (1);
}
