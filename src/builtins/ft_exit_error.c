/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:22:06 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/19 17:25:08 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_error(int *exit_code, t_glob *envp, t_exec *exec)
{
	*exit_code = 2;
	envp->utils->return_code = 2;
	free_exit(exec, envp);
	exit(*exit_code);
}
