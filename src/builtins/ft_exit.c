/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:48:41 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/19 19:01:27 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_get_alpha(char **arg)
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

t_bool	is_limit(char **number, int i, int j)
{
	char	*long_max;
	char	*long_min;
	t_bool	flg;

	long_max = "9223372036854775807";
	long_min = "-9223372036854775808";
	flg = FALSE;
	while (number[j] == ' ')
		j++;
	if ((number[0] == '-' && (int)ft_strlen(number) - j >= 21)
		|| (number[0] != '-' && (int)ft_strlen(number) - j >= 20))
		return (TRUE);
	if (number[0] == '-')
	{
		flg = check_limits(number, long_min, i, j);
		if (flg)
			ft_putstr_fd("exit\n numeric argument required\n", 2);
		return (flg);
	}
	flg = check_limits(number, long_max, i, j);
	if (flg)
		ft_putstr_fd("exit\n numeric argument required\n", 2);
	return (flg);
}

void	free_exit(t_exec *exec, t_glob *t_envp)
{
	int		i;
	t_glob	*tmp_glob;
	t_exec	*tmp_exec;

	tmp_glob = NULL;
	tmp_exec = NULL;
	while (exec)
	{
		i = 0;
		tmp_exec = exec;
		exec = exec->next;
		while (tmp_exec->flags && tmp_exec->flags[i])
		{
			free(tmp_exec->flags[i]);
			tmp_exec->flags[i] = NULL;
			i++;
		}
		free_exit_tmp_exec(tmp_exec);
	}
	tmp_glob = t_envp;
	t_envp = t_envp->next;
	free(tmp_glob);
	free_exit_envp(t_envp);
	rl_clear_history();
}

void	ft_exit(int fd, t_exec *exec, t_glob **t_envp, int *return_value)
{
	int		exit_code;
	t_bool	error_arg;

	exit_code = (*t_envp)->utils->return_code;
	error_arg = FALSE;
	if (!exec->flags[1] && !exec->is_piped)
		handle_exit_error(0, *t_envp, exec, &exit_code);
	if (is_limit(exec->flags, 0, 0) || ft_get_alpha(exec->flags))
		error_arg = TRUE;
	if (exec->flags[2] && !error_arg && !ft_get_alpha(exec->flags[1]))
	{
		(*t_envp)->utils->return_code = 1;
		ft_putstr_fd("exit\n too many arguments\n", 2);
		(*t_envp)->utils->return_code = 1;
		*return_value = 1;
		return ;
	}
	if (error_arg)
		handle_error(&exit_code, *t_envp, exec);
	else if (exec->flags[1])
		exit_code = ft_atoi(exec->flags[1]);
	*return_value = calculate_exit_code(exit_code);
	(*t_envp)->utils->return_code = *return_value;
	if (!exec->is_piped)
		handle_exit_error(fd, *t_envp, exec, return_value);
}

void	free_envp(t_glob *t_envp)
{
	t_glob	*tmp_glob;

	tmp_glob = NULL;
	tmp_glob = t_envp;
	t_envp = t_envp->next;
	free(tmp_glob);
	while (t_envp)
	{
		tmp_glob = t_envp;
		t_envp = t_envp->next;
		if (tmp_glob->name)
			free(tmp_glob->name);
		if (tmp_glob->content)
			free(tmp_glob->content);
		free(tmp_glob);
		tmp_glob = NULL;
	}
	rl_clear_history();
}