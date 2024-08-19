/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:22:06 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/19 15:25:57 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_error(int *exit_code, t_glob *envp)
{
	*exit_code = 2;
	envp->utils->return_code = 2;
}
