/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:22:06 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/20 17:02:46 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_exit_error(t_glob *t_envp, t_exec *exec, int *exit_code)
{
	ft_putstr_fd("exit\n", 2);
	free_exit(exec, t_envp);
	exit(*exit_code);
}

void	handle_exit(t_glob *t_envp, t_exec *exec, int *exit_code)
{
	ft_putstr_fd("exit\n", 2);
	free_exit(exec, t_envp);
	exit(*exit_code);
}

void	handle_error(int *exit_code, t_glob *envp, t_exec *exec)
{
	ft_putstr_fd("exit\n numeric argument required\n", 2);
	*exit_code = 2;
	envp->utils->return_code = 2;
	free_exit(exec, envp);
	exit(*exit_code);
}
