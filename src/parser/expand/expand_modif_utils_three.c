/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_modif_utils_three.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 23:13:57 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/20 23:19:37 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_expand_modif_three(char **content, int *start, int *end)
{
	*content = "";
	*start = 0;
	*end = 0;
}

int	ft_expand_modif_two_early(char *arg, int i, t_bool *d_quote)
{
	if (arg[i] == '"')
	{
		*d_quote = TRUE;
		i++;
	}
	if (arg[i] == '\'' && *d_quote == FALSE)
	{
		i++;
		while (arg[i] != '\'')
			i++;
	}
	else if (arg[i] == '"')
	{
		*d_quote = FALSE;
		i++;
	}
	return (i);
}

int	ft_expand_modif_two_mid(int *start, int i, int *end, char *arg)
{
	*start = i;
	i++;
	while ((arg[i] >= 'a' && arg[i] <= 'z') || (arg[i] >= 'A' && arg[i] <= 'Z')
		|| (arg[i] >= '0' && arg[i] <= '9') || arg[i] == '_')
		i++;
	*end = i;
	return (i);
}

int	ft_expand_modif_one(char *arg, int i, int *start, int *end)
{
	while (arg[i] != '$' && arg[i + 1] != '?')
		i++;
	*start = i + 1;
	*end = *start + 1;
	return (i);
}
