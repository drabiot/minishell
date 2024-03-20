/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:19:50 by nberduck          #+#    #+#             */
/*   Updated: 2024/03/20 17:20:35 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_verif_args(t_list *t_args)
{
	unsigned int	i;
	char			*content;
	
	while (t_args)
	{
		content = (char *)t_args->content;
		printf("%s\n", content);
		if (content[0] >= '0' && content[0] <= '9')
		{
			printf("export: '%s': not a valid identifier\n", content);
			return (1);
		}
		i = 0;
		while (content[i])
		{
			if(!(content[i] >= 'a' && content[i] <= 'z') && !(content[i] >= 'A' && content[i] <= 'Z'))
			{
				printf("export: '%s': not a valid identifier\n", content);
				return (1);
			}
			i++;
		}
		t_args = t_args->next;
	}
	return (0);
}
static void	ft_env_print(t_list *t_envp)
{
	t_list			*tmp;
	char			*content;
	unsigned int	i;
	int				name_end;
	

	tmp = t_envp;
	while (tmp)
	{
		i = 0;
		name_end = 0;
		content = (char *)tmp->content;
		printf("declare -x ");
		while (content[i] && name_end != -1)
		{
			if (content[i] == '=')
				name_end = -1;
			printf("%c", content[i]);
			i++;
		}
		printf("\"%s\"\n", &content[i + 1]);
		tmp = tmp->next;
   }
}

int	ft_export(t_list **t_envp, char **args)
{
	t_list	*t_args;
	t_list	*curr;
	t_list	*tmp;
	t_args = split_args(args);
	if (!t_args)
		ft_env_print(*t_envp);
	if (!ft_verif_args(t_args))
	{
		curr = t_args;
		while (curr)
		{
			tmp = ft_lstnew(ft_strdup(curr->content));
			ft_lstadd_back(t_envp, tmp);
		curr = curr->next;
		}
	}
	else
		return (1);
	return (0);
}
