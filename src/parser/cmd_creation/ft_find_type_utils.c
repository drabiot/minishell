/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_type_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:20:28 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/16 16:20:47 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_start(t_cmd *prev)
{
	if (!prev)
		return (0);
	if (prev->type == PIPE || prev->type == LIMITER
		|| prev->type == REDIR_FILE)
		return (1);
	return (0);
}
