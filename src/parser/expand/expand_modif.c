/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_modif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:50:01 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/20 23:19:26 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	handle_typ_one(t_cmd *cmd, t_glob *t_envp, t_expand_ctx *ctx, int *i)
{
	*i = ft_expand_modif_one(cmd->arg, *i, &ctx->start, &ctx->end);
	ctx->content = ft_itoa(t_envp->utils->return_code);
	ctx->mal_cont = TRUE;
}

void	handle_type_two(t_cmd *cmd, t_glob *t_envp, t_expand_ctx *ctx, int *i)
{
	while (cmd->arg[*i])
	{
		*i = ft_expand_modif_two_early(cmd->arg, *i, &ctx->d_quote);
		if (cmd->arg[*i] == '$')
		{
			*i = ft_expand_modif_two_mid(&ctx->start, *i, &ctx->end, cmd->arg);
			ctx->name = ft_substr(cmd->arg, ctx->start + 1,
					ctx->end - ctx->start - 1);
			ctx->content = ft_getenv(ctx->name, t_envp, 0);
			free(ctx->name);
			ctx->name = NULL;
			ctx->start++;
			break ;
		}
		(*i)++;
	}
}

static void	handle_type_default(t_expand_ctx *ctx)
{
	ft_expand_modif_three(&ctx->content, &ctx->start, &ctx->end);
}

static void	free_content_if_needed(t_expand_ctx *ctx)
{
	if (ctx->mal_cont && ctx->content)
	{
		free(ctx->content);
		ctx->content = NULL;
	}
}

void	ft_expand_modif(t_cmd *cmd, t_glob *t_envp, int type, int i)
{
	t_expand_ctx	ctx;

	ctx.start = 0;
	ctx.end = 0;
	ctx.content = NULL;
	ctx.name = NULL;
	ctx.d_quote = FALSE;
	ctx.mal_cont = FALSE;
	if (type == 1)
		handle_typ_one(cmd, t_envp, &ctx, &i);
	else if (type == 2)
		handle_type_two(cmd, t_envp, &ctx, &i);
	else
		handle_type_default(&ctx);
	if (!ctx.content)
		ctx.content = "";
	ft_expd_do(cmd, ft_substr(ctx.content, 0, ft_strlen(ctx.content)),
		ctx.start, ctx.end - 1);
	free_content_if_needed(&ctx);
}
