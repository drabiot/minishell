/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:54:39 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/21 01:22:35 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_glob *t_envp, int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	if (pwd)
		free(pwd);
	t_envp->utils->return_code = 0;
	return (0);
}
