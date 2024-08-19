/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:37:32 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/19 20:45:03 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_glob	*t_envp;
	t_cwd	path;
	char	**env;

	(void)argc;
	(void)argv;
	env = NULL;
	if (envp)
		env = envp;
	generate_key_random();
	path = (t_cwd){0};
	path.return_code = 0;
	t_envp = ft_envp_creation(env);
	add_glob_utils(t_envp, &path);
	while (TRUE)
	{
		prompt(t_envp);
	}
	return (0);
}
