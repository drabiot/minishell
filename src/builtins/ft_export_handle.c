/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:52:02 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/19 17:03:19 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_state(t_glob **t_envp, t_exec *exec, int state, int *error)
{
	if (state > 0)
	{
		*error = TRUE;
		return (state);
	}
	if (no_glob(t_envp, exec->flags[0]))
		ft_lstadd_back_alpha_envp(t_envp, ft_globsolo_creation(exec->flags[0]));
	else if (state != 0)
		change_glob(t_envp, exec->flags[0], state, 0);
	return (state);
}
