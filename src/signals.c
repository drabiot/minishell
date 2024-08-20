/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:14:34 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/20 14:38:02 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	replace_line(int sign)
{
	/*g_return_nbr = 130;*/
	write (1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sign;
}

void	quit_n(int sign)
{
	/*g_return_nbr = 130;*/
	write (1, "\n", 1);
	(void)sign;
}

void	quit_slash(int sign)
{
	/*g_return_nbr = 131;*/
	printf("Quit\n");
	(void)sign;
}

void	ft_signal(int sign)
{
	if (sign == 1)
	{
		signal(SIGINT, replace_line);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sign == 2)
	{
		signal(SIGINT, quit_n);
		signal(SIGQUIT, quit_slash);
	}
}
