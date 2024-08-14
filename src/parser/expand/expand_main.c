/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:49:58 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/14 16:43:11 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_bool	other_expand(char *arg, int **type, int i, int quote)
{
	quote = -1;
	if (i > 0 && (arg[i - 1] == '"' || arg[i - 1] == '\''))
		quote = i - 1;
	if (arg[i + 1] == '\0' || arg[i + 1] == ' '
		|| (quote != -1 && arg[i + 1] == arg[quote]) || arg[i + 1] == '='
		|| arg[i + 1] == '.')
	{
		**type = 3;
		return (FALSE);
	}
	while (arg[i])
	{
		//if (arg[i] == '"' || arg[i] == '\'')
		//	quote = i;
		if (!((arg[i] >= 'a' && arg[i] <= 'z')
				&& (arg[i] >= 'A' && arg[i] <= 'Z')
				&& (arg[i] >= '0' && arg[i] <= '9')))
		{
			**type = 2;
			return (TRUE);
		}
		//if (arg[i] == arg[quote] && quote != -1 && i != quote)
		//	quote = -1;
		i++;
	}
	return (FALSE);
}

t_bool	is_expandable_dollar(char *arg, int i, int *type, t_bool d_quote)
{
	if (arg[i + 1] == '?')
	{
		*type = 1;
		return (TRUE);
	}
	else if ((arg[i + 1] == '\'' || arg[i + 1] == '"') && d_quote)
		return (FALSE);
	else if (other_expand(arg, &type, i, 0))
		return (TRUE);
	else
		return (FALSE);
}

int	is_expendable_e(char *arg, int i, t_bool *d_quote, t_bool *s_quote)
{
	if (arg[i] == '"' && !*s_quote && arg[i + 1] != '"')
	{
		if (*d_quote == FALSE)
			*d_quote = TRUE;
		else
			*d_quote = FALSE;
		i++;
	}
	else if (arg[i] == '"' && !*s_quote)
		i++;
	if (arg[i] == '\'' && !*d_quote && arg[i + 1] != '\'')
	{
		if (*s_quote == FALSE)
			*s_quote = TRUE;
		else
			*s_quote = FALSE;
		i++;
	}
	else if (arg[i] == '\'' && !*s_quote)
		i++;
	return (i);
}

static t_bool	is_expandable(char *arg, int *type, t_bool d_quote, int i)
{
	t_bool	s_quote;
	t_bool	b_dollar;

	b_dollar = FALSE;
	s_quote = FALSE;
	while (arg && i < (int)ft_strlen(arg))
	{
		i = is_expendable_e(arg, i, &d_quote, &s_quote);
		if (arg[i] == '$' && !s_quote)
		{
			b_dollar = is_expandable_dollar(arg, i, type, d_quote);
			return (b_dollar);
		}
		else
			i++;
	}
	return (FALSE);
}

void	ft_expand(t_cmd **list, t_glob *t_envp)
{
	t_cmd	*tmp;
	int		type;

	tmp = *list;
	type = 0;
	while (tmp)
	{
		while (is_expandable(tmp->arg, &type, FALSE, 0))
			ft_expand_modif(tmp, t_envp, type, 0);
		tmp = tmp->next;
	}
}
