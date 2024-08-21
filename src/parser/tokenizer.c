/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:37:32 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/21 01:45:21 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	grab_token(t_input *cmd, t_token *token)
{
	int	quote;

	quote = -1;
	while (cmd->str[cmd->i + 1] && is_white_space(cmd->str, cmd->i))
		cmd->i++;
	token->start = cmd->i;
	if (is_redirection(cmd, token))
		return ;
	if (quote == -1 && (cmd->str[cmd->i] == '\'' || cmd->str[cmd->i] == '"'))
		quote = cmd->i;
	else if (quote != -1 && cmd->str[cmd->i] == cmd->str[quote])
		quote = -1;
	while (cmd->str[cmd->i + 1] && (quote != -1
			|| !(is_white_space(cmd->str, cmd->i + 1)
				|| is_special_char(cmd->str, cmd->i + 1))))
	{
		cmd->i++;
		if (quote == -1 && (cmd->str[cmd->i] == '\''
				|| cmd->str[cmd->i] == '"'))
			quote = cmd->i;
		else if (quote != -1 && cmd->str[cmd->i] == cmd->str[quote])
			quote = -1;
	}
	token->end = cmd->i;
}

static char	*check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if (arg[i] != ' ')
			return (arg);
		i++;
	}
	if (arg)
		free(arg);
	return (NULL);
}

static void	ft_start_exec(t_cmd *start, t_glob *t_envp, t_input *cmd)
{
	if (!is_error_syntax(start, t_envp, cmd))
		t_envp->utils->return_code = ft_execution_main(&t_envp, start);
	else
		free_t_cmd(start);
}

void	tokenizer(t_input *cmd, t_glob *t_envp, unsigned int index)
{
	t_token				token;
	t_cmd				*start;
	char				*arg;
	char				c;

	start = NULL;
	token = (t_token){0};
	while (cmd->str && cmd->str[cmd->i])
	{
		grab_token(cmd, &token);
		c = cmd->str[token.end + 1];
		cmd->str[token.end + 1] = 0;
		arg = ft_substr(cmd->str, token.start, token.end - token.start + 1);
		arg = check_arg(arg);
		if (arg)
			ft_lstadd_back_cmd(&start, ft_cmd_creation(arg, index, start));
		cmd->str[token.end + 1] = c;
		cmd->i++;
		index++;
	}
	ft_expand(&start, t_envp);
	expandable_type(start);
	handle_quote(start);
	ft_start_exec(start, t_envp, cmd);
}
