/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:12:44 by adorlac           #+#    #+#             */
/*   Updated: 2024/07/09 14:33:05 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/libft.h"

// static t_bool	is_white_space(char *str, int i)
// {
// 	if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
// 		return (1);
// 	return (0);
// }

// static t_bool	is_special_char(char *str, int i)
// {
// 	if (str[i] == '|' || str[i] == '<' || str[i] == '>')
// 		return (1);
// 	return (0);
// }

// static t_bool	is_redirection(t_input *cmd, t_token *token)
// {
// 	char	c;

// 	c = cmd->str[cmd->i];
// 	if (!(c == '>' || c == '<' || c == '|'))
// 		return (0);
// 	if ((c == '>' || c == '<') && c == cmd->str[cmd->i + 1])
// 		cmd->i++;
// 	token->end = cmd->i;
// 	return (1);
// }

// static void	grab_token(t_input *cmd, t_token *token)
// {
// 	char	quote;

// 	quote = 0;
// 	while (cmd->str[cmd->i + 1] && is_white_space(cmd->str, cmd->i))
// 		cmd->i++;
// 	token->start = cmd->i;
// 	if (is_redirection(cmd, token))
// 		return ;
// 	while (cmd->str[cmd->i + 1] && (!(is_white_space(cmd->str, cmd->i + 1)
// 				|| is_special_char(cmd->str, cmd->i + 1))
// 				|| (quote == 0 && (cmd->str[cmd->i] != '\''
// 				|| cmd->str[cmd->i] != '"'))))
// 	{
// 		quote = cmd->str[cmd->i];
// 		if (quote == '\'' || quote == '"')
// 		{
// 			while (cmd->str[cmd->i + 1] && quote != cmd->str[cmd->i + 1])
// 				cmd->i++;
// 			cmd->i++;
// 		}
// 		if (!(is_white_space(cmd->str, cmd->i + 1)
// 				|| is_special_char(cmd->str, cmd->i + 1)))
// 			cmd->i++;
// 	}
// 	token->end = cmd->i;
// }

t_cmd	*expand_tokenizer(t_input *cmd)
{
	unsigned int		index;
	t_token				token;
	t_cmd				*start;
	char				*arg;
	char				c;

	index = 0;
	start = NULL;
	token = (t_token){0};
	while (cmd->str[cmd->i])
	{
		grab_token(cmd, &token);
		c = cmd->str[token.end + 1];
		cmd->str[token.end + 1] = 0;
		// printf("start: %d, end: %d (%s)\n", token.start, token.end, &cmd->str[token.start]);
		arg = ft_substr(cmd->str, token.start, token.end - token.start + 1);
		ft_lstadd_back_cmd(&start, ft_cmd_creation(arg, index, start));
		cmd->str[token.end + 1] = c;
		cmd->i++;
		index++;
	}
	return (start);
}
