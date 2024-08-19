/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:12:44 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/19 23:00:58 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/libft.h"

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
		arg = ft_substr(cmd->str, token.start, token.end - token.start + 1);
		ft_lstadd_back_cmd(&start, ft_cmd_creation(arg, index, start));
		cmd->str[token.end + 1] = c;
		cmd->i++;
		index++;
	}
	return (start);
}
