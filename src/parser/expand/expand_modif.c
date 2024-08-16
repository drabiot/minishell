/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_modif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:50:01 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/16 17:03:38 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*static void	free_array(char ***array)
{
	int	i;

	i = 0;
	while (*array && (*array)[i])
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	if (*array)
		free(*array);
	*array = NULL;
}*/

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
		|| (arg[i] >= '0' && arg[i] <= '9'))
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

void	ft_expand_modif(t_cmd *cmd, t_glob *t_envp, int type, int i)
{
	int		start;
	int		end;
	char	*content;
	char	*name;
	t_bool	d_quote;
	t_bool	mal_cont;

	start = 0;
	end = 0;
	name = NULL;
	content = NULL;
	d_quote = FALSE;
	mal_cont = FALSE;
	if (type == 1)
	{
		i = ft_expand_modif_one(cmd->arg, i, &start, &end);
		content = ft_itoa(t_envp->utils->return_code);
		mal_cont = TRUE;
	}
	else if (type == 2)
	{
		while (cmd->arg[i])
		{
			i = ft_expand_modif_two_early(cmd->arg, i, &d_quote);
			if (cmd->arg[i] == '$')
			{
				i = ft_expand_modif_two_mid(&start, i, &end, cmd->arg);
				name = ft_substr(cmd->arg, start + 1, end - start - 1);
				content = ft_getenv(name, t_envp, 0);
				if (name)
				{
					free(name);
					name = NULL;
				}
				start++;
				break ;
			}
			i++;
		}
	}
	else
		ft_expand_modif_three(&content, &start, &end);
	if (!content)
		content = "";
	ft_expd_do(cmd, ft_substr(content, 0, ft_strlen(content)), start, end - 1);
	if (mal_cont && content)
	{
		free (content);
		content = NULL;
	}

}
