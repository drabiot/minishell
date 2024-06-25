/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:37:32 by tchartie          #+#    #+#             */
/*   Updated: 2024/06/25 19:20:37 by tchartie         ###   ########.fr       */
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

void	grab_token(t_input *cmd, t_token *token)
{
	char	quote;

	quote = 0;
	while (cmd->str[cmd->i + 1] && is_white_space(cmd->str, cmd->i))
		cmd->i++;
	token->start = cmd->i;
	if (is_redirection(cmd, token))
		return ;
	while (cmd->str[cmd->i + 1] && (!(is_white_space(cmd->str, cmd->i + 1)
				|| is_special_char(cmd->str, cmd->i + 1))
				|| (quote == 0 && (cmd->str[cmd->i] != '\''
				|| cmd->str[cmd->i] != '"'))))
	{
		quote = cmd->str[cmd->i];
		if (quote == '\'' || quote == '"')
		{
			while (cmd->str[cmd->i + 1] && quote != cmd->str[cmd->i + 1])
				cmd->i++;
			cmd->i++;
		}
		if (!(is_white_space(cmd->str, cmd->i + 1)
				|| is_special_char(cmd->str, cmd->i + 1)))
			cmd->i++;
	}
	token->end = cmd->i;
}

void	tokenizer(t_input *cmd, t_glob *t_envp)
{
	unsigned int		index = 0;
	t_token				token;
	t_cmd				*start;
	char				*arg;

	start = NULL;
	token = (t_token){0};
	while (cmd->str[cmd->i])
	{
		grab_token(cmd, &token);
		char c = cmd->str[token.end + 1];
		cmd->str[token.end + 1] = 0;
		// printf("start: %d, end: %d (%s)\n", token.start, token.end, &cmd->str[token.start]);
		arg = ft_substr(cmd->str, token.start, token.end-token.start+1);
		ft_lstadd_back_cmd(&start, ft_cmd_creation(arg, index, start));
		cmd->str[token.end + 1] = c;
		cmd->i++;
		index++;
	}
	ft_expand(&start, t_envp);
	handle_quote(start);
	// t_cmd *test;
	// tmp = t_envp;
	// while (tmp)
	// {
	// 	printf("name :%s, content:%s.\n", tmp->name, tmp->content);
	// 	tmp = tmp->next;
	// }

	// printf("%i|\n", start->next->type);
	// test = ft_cut_cmd(start);
	// t_cmd *tmp = start;
	// while (tmp)
	// {
	// 	printf("arg :%s, type :%i, index,%i\n", tmp->arg, tmp->type, tmp->index);
	// 	tmp = tmp->next;
	// }
	// ft_lstclear_cmd(&test);
	ft_execution_main(&t_envp, start);
	// if (t_envp->utils->return_code)
	// 	exit (t_envp->utils->return_code);
	// ft_export(&t_envp, start);
	// ft_unset(&t_envp, start);
	// tmp = t_envp;
	// while (tmp)
	// {
	// 	printf("name : %s,equal : %i,content : %s.\n", tmp->name, tmp->equal, tmp->content);
	// 	tmp = tmp->next;
	// }
	// (void)t_envp;
	//if (start)
	//ft_lstclear_cmd(&start);
}
