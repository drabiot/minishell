/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:51:13 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/21 21:55:51 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_bool	unset_pwds(char *type, t_glob *t_envp)
{
	while (t_envp && ft_strcmp(t_envp->name, type) != 0)
		t_envp = t_envp->next;
	if (ft_strcmp(t_envp->name, type) == 0)
	{
		if (t_envp->equal == 30)
			return (TRUE);
		else
			return (FALSE);
	}
	return (FALSE);
}

void	check_pwd(t_expand_ctx *ctx, t_glob *t_envp)
{
	if (ctx->name && ft_strcmp("PWD", ctx->name) == 0
		&& unset_pwds("PWD", t_envp))
		ctx->content = "";
	if (ctx->name && ft_strcmp("OLDPWD", ctx->name) == 0
		&& unset_pwds("OLDPWD", t_envp))
		ctx->content = "";
}
