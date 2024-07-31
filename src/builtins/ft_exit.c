/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:48:41 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/31 22:14:17 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_get_alpha(char *arg)
{
	int	i;

	i = 0;
	while (is_white_space(arg, i))
		i++;
	if (arg && (arg[i] == '-' || arg[i] == '+'))
		i++;
	while (arg && arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

static t_bool	is_limit(char *number)
{
	char	*long_max;
	char	*long_min;
	int		i;
	int		j;
	int		diff;
	t_bool	is_out;

	long_max = "9223372036854775807";
	long_min = "-9223372036854775808";
	i = 0;
	j = 0;
	diff = 1;
	is_out = FALSE;
	while (number[j] == ' ')
		j++;
	if (number[0] == '-' && (int)ft_strlen(number) - j >= 21)
		return (TRUE);
	if (number[0] != '-' && (int)ft_strlen(number) - j >= 20)
		return (TRUE);
	if (number[0] == '-')
	{
		while (number[i + j] && !is_out)
		{
			diff = number[i + j] - long_min[i];
			if (diff < 0)
				is_out = TRUE;
			i++;
		}
		if (diff > 0)
			return (TRUE);
		i++;
	}
	else
	{
		while (number[i + j] && !is_out)
		{
			diff = number[i + j] - long_max[i];
			if (diff < 0)
				is_out = TRUE;
			i++;
		}
		if (diff > 0)
			return (TRUE);
	}
	return (FALSE);
}

void	ft_exit(int fd, t_exec *exec, t_glob **t_envp, int *return_value)
{
	int		exit_code;
	t_bool	error_arg;

	exit_code = (*t_envp)->utils->return_code;
	error_arg = FALSE;
	if (!exec->flags[1] && !exec->is_piped)
	{
		ft_putstr_fd("exit\n", 0);
		exit(exit_code);
	}
	if (!ft_get_alpha(exec->flags[1]) && is_limit(exec->flags[1]))
		error_arg = TRUE;
	if (exec->flags[2] && !error_arg && !ft_get_alpha(exec->flags[1]))
	{
		(*t_envp)->utils->return_code = 1;
		ft_putstr_fd("exit\n too many arguments\n", 2);
		(*t_envp)->utils->return_code = 1;
		*return_value = 1;
		return ;
	}
	if (ft_get_alpha(exec->flags[1]) || error_arg)
	{
		(*t_envp)->utils->return_code = 2;
		ft_putstr_fd(" numeric argument required\n", 2);
		exit_code = 2;
		*return_value = 2;
		error_arg = TRUE;
	}
	if (exec->flags[1] && !error_arg)
		exit_code = ft_atoi(exec->flags[1]);
	if (exit_code >= 256)
		exit_code %= 256;
	if (exit_code < 0)
		exit_code = 256 - (-exit_code) % 256;
	(*t_envp)->utils->return_code = exit_code;
	if (!exec->next)
	{
		ft_putstr_fd("exit\n", fd);
		exit (exit_code);
	}
}
