/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:52:02 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/19 18:49:28 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_state(t_glob **t_envp, t_exec *exec, int state, int i)
{
	if (state > 0)
		return (state);
	if (no_glob(t_envp, exec->flags[i]))
		ft_lstadd_back_alpha_envp(t_envp, ft_globsolo_creation(exec->flags[i]));
	else if (state != 0)
		change_glob(t_envp, exec->flags[i], state, 0);
	return (state);
}
