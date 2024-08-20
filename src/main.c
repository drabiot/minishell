/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:37:32 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/20 19:26:36 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	create_pwds(t_glob **glob)
{
	t_glob	*tmp;
	char	*content_pwd;

	content_pwd = getcwd(NULL, 0);
	if (!content_pwd)
		content_pwd = NULL;
	tmp = ft_lstnew_glob(ft_strdup("PWD"), 1, content_pwd);
	ft_lstadd_back_alpha_envp(glob, tmp);
	tmp = ft_lstnew_glob(ft_strdup("OLDPWD"), 0, NULL);
	ft_lstadd_back_alpha_envp(glob, tmp);
}

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
	if (!*envp)
		create_pwds(&t_envp);
	while (TRUE)
	{
		prompt(t_envp);
	}
	return (0);
}
