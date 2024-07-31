/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:12:56 by adorlac           #+#    #+#             */
/*   Updated: 2024/07/31 21:15:35 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_bool	other_expand(char *arg, int **type, int i)
{
	int	quote;

	quote = -1;
	if (arg[i - 1] == '"' || arg[i - 1] == '\'')
		quote = i - 1;
	if (arg[i + 1] == '\0' || arg[i + 1] == ' ' || (arg[i + 1] == arg[quote] && quote != -1) || arg[i + 1] == '=' || arg[i + 1] == '.')
	{
		**type = 3;
		return (FALSE);
	}
	while (arg[i])
	{
		//if (arg[i] == '"' || arg[i] == '\'')
		//	quote = i;
		if (!((arg[i] >= 'a' && arg[i] <= 'z') && (arg[i] >= 'A' && arg[i] <= 'Z')
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

static t_bool	is_expandable(char *arg, int *type)
{
	int		i;
	t_bool	d_quote;
	t_bool	s_quote;

	i = 0;
	d_quote = FALSE;
	s_quote = FALSE;
	while (arg[i])
	{
		if (arg[i] == '"' && !s_quote && arg[i + 1] != '"')
		{
			d_quote = !d_quote;
			i++;
		}
		else if (arg[i] == '"' && !s_quote)
			i++;
		if (arg[i] == '\'' && !d_quote && arg[i + 1] != '\'')
		{
			s_quote = !s_quote;
			i++;
		}
		else if (arg[i] == '\'' && !s_quote)
			i++;
		if (arg[i] == '$' && !s_quote)
		{
			if (arg[i + 1] == '?')
			{
				*type = 1;
				return (TRUE);
			}
			else if ((arg[i + 1] == '\'' || arg[i + 1] == '"') && d_quote)
				return (FALSE);
			else if (other_expand(arg, &type, i))
				return (TRUE);
			else
				return (FALSE);
		}
		/*else if (arg[i] == '"' && d_quote)
			;
		else if (arg[i] == '\'' && s_quote)
			;*/
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
		while (is_expandable(tmp->arg, &type))
			ft_expand_modif(tmp, t_envp, type);
		tmp = tmp->next;
	}
}
