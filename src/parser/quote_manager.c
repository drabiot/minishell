/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:55:59 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/15 07:50:35 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	delete_char(char *arg, int pos)
{
	int	i;
	int	end;

	i = 0;
	end = ft_strlen(arg) - 1;
	while (i <= end)
	{
		if (i == pos)
		{
			while (i <= end)
			{
				arg[i] = arg[i + 1];
				i++;
			}
			arg[i] = '\0';
			break ;
		}
		i++;
	}
}

static void	apply_del_quote(char *arg, int *i)
{
	delete_char(arg, *i);
	while (arg[*i] && arg[*i] != '\"')
	{
		(*i)++;
	}
	if (arg[*i] == '\"')
		delete_char(arg, *i);
	(*i)--;
}

static void	remove_quote(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\"')
			apply_del_quote(arg, &i);
		else if (arg[i] == '\'')
		{
			delete_char(arg, i);
			while (arg[i] && arg[i] != '\'')
				i++;
			if (arg[i] == '\'')
				delete_char(arg, i);
			i--;
		}
		i++;
	}
}

void	handle_quote(t_cmd *start)
{
	while (start)
	{
		if (start->arg)
			remove_quote(start->arg);
		start = start->next;
	}
}
