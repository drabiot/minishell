/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_verif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:15:38 by nberduck          #+#    #+#             */
/*   Updated: 2024/03/29 00:05:31 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	ft_verif_quote(char *arg)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
			quote = 1;
		else if (arg[i] == '"')
			quote = 0;
		else if (arg[i] == '$')
			return (quote);
		i++;
	}
	return (1);
}

static int	ft_verif_name(char *arg)
{
	int i;

	i = 0;
	while (arg[i] && arg[i] != '$')
		i++;
	if (arg[i + 1] >= '0' && arg[i + 1] <= '9')
		return (1);
	// if (!(arg[i + 1] >= 'a' && arg[i + 1] <= 'z') && !(arg[i + 1] >= 'A' && arg[i + 1] <= 'Z') && arg[i + 1] != '_')
	// 	return (1);
	return (0);
}

int ft_verif_main(char *arg)
{
	if (ft_verif_quote(arg) || ft_verif_name(arg))
		return (1);
	return (0);
}