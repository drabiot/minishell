/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:14:34 by adorlac           #+#    #+#             */
/*   Updated: 2024/08/21 02:40:17 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	replace_line(int sign)
{
	g_sig = SIGINT;
	write (1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sign;
}

void	here_doc(int sign)
{
	char	c;

	g_sig = SIGINT;
	c = '\n';
	ioctl(0, TIOCSTI, &c);
	rl_on_new_line();
	rl_replace_line("", 0);
	(void)sign;
}

void	quit_n(int sign)
{
	g_sig = SIGINT;
	write (1, "\n", 1);
	(void)sign;
}

void	quit_slash(int sign)
{
	g_sig = 131;
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
	if (sign == 3)
	{
		signal(SIGINT, here_doc);
	}
}
