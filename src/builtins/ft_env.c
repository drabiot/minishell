/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:30:20 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/09 14:44:20 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(int fd, t_glob **t_envp)
{
	t_glob			*tmp;
	char			*first_part;
	char			*last_part;

	if (!*t_envp)
		return (1);
	tmp = *t_envp;
	while (tmp)
	{
		first_part = ft_strjoin(tmp->name, "=");
		last_part = ft_strjoin(first_part, tmp->content);
		ft_putstr_fd(last_part, fd);
		ft_putstr_fd("\n", fd);
		free(first_part);
		free(last_part);
		tmp = tmp->next;
	}
	return (0);
}
