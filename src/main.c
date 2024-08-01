/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:54:59 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/01 17:31:39 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_name_len(char *tmp)
{
	int	i;

	if (!tmp)
		return (0);
	i = 0;
	while (tmp[i] != '=' && tmp[i])
		i++;
	return (i);
}

void	ft_lstadd_back_alpha_envp(t_glob **list, t_glob *new)
{
	t_glob	*tmp;
	t_glob	*last;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	last = NULL;
   //printf("name: %s, equal: %d, content: %s\n", new->name, new->equal, new->content);
	while (tmp->next)
	{
      // if (ft_strcmp(tmp->name, new->name) != 0)
      // {
      //    if (!last)
      //    {
      //       *list = new;
      //       new->next = tmp;
      //       return ;
      //    }
      //    last->next = new;
      //    new->next = tmp;
      //    return ;  
      // }
		if (ft_strcmp(tmp->name, new->name) == 0)
		{
			if (new->equal == 0)
			{
				ft_lstdelone_glob(new);
				return ;
			}
			free(tmp->content);
			tmp->content = ft_strdup(new->content);
			tmp->equal = 1;
			ft_lstdelone_glob(new);
			return ;
		}
		last = tmp;
		tmp = tmp->next;
	}
	if (new->equal == 1)
		ft_lstadd_back_glob(list, new);
   // while ((*list)->next)
   // {
   //    *list = (*list)->next;
   // }
   // printf("name: %s\n", (*list)->name);
}

t_glob	*ft_envp_creation(char **envp)
{
	t_glob			*list;
	t_glob			*tmp;
	char			*name;
	char			*content;
	int				name_end;
	char			**env;
	unsigned int	i;

	i = 0 ;
	list = NULL;
	env = NULL;
	if (envp)
		env = envp;
	while (envp[i])
	{
		name_end = ft_name_len(envp[i]);
		name = ft_substr(envp[i], 0, name_end);
		content = ft_substr(envp[i], name_end + 1, ft_strlen(envp[i]));
		if (envp[i][name_end] && envp[i][name_end] == '=')
			tmp = ft_lstnew_glob(name, 1, content, env);
		else
			tmp = ft_lstnew_glob(name, 0, content, env);
		ft_lstadd_back_alpha_envp(&list, tmp);
		i++;
	}
	return (list);
}

static void	ft_envp_print(t_glob *t_envp)
{
	int	i;

	i = 0;
	t_glob *tmp;
	tmp = t_envp;
	while (tmp)
	{
		printf("name: %s, equal:%i, content: %s.\n",
		(char *)tmp->name, (int)tmp->equal, (char *)tmp->content);
		printf("%i\n", i);
		tmp = tmp->next;
		i++;
	}
}

void	ft_signal(int sign)
{
	if (sign == SIGINT)
	{
		write (1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		(void)sign;
	}
	if (sign == SIGQUIT)
	{
		ft_putstr_fd("Quit", 2);
		write (1, "\n", 1);
		(void)sign;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_glob	*t_envp;
	int		exit;
	t_cwd	path;

	path = (t_cwd){0};
	path.return_code = 0;
	// int  ret;

	// (void)argc;
	// (void)argv;
	// (void)envp;
	// ret = prompt();
	// return (ret);

	(void)argc;
	// (void)envp;
	(void)argv;

	t_envp = ft_envp_creation(envp);
	add_glob_utils(t_envp, &path);
	// ft_envp_print(t_envp);
	// ft_lstclear(&t_envp, free);

	// ft_echo(argv[1], 1);

	// char  *str;
	// str = ft_pwd();
	// printf("%s\n", str);
	// free(str);

	// ft_env(envp);

	// printf("\n\nUnset\n\n");
	// ft_unset(&t_envp, &argv[1]);
	// ft_envp_print(t_envp);

	// ft_export(&t_envp, &argv[1]);
	// ft_envp_print(t_envp);

	// ft_cd(argv[1]);

	// ft_exit(ft_atoi(argv[1]));

	// ft_envp_print(t_envp);

	//Part for signal
	//Need static function ft_signal

	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	// signal(,ft_signal);
	// while (1)
	//		pause();


	exit = -1;
	while (exit != 0)
	{
		exit = prompt(t_envp);
	}
	// t_list *tmp;

	// tmp = t_envp;
	// while (tmp)
	// {
	//    printf("%s\n", (char *)tmp->content);
	//    tmp = tmp->next;
	// }
	ft_envp_print(NULL);
	ft_lstclear_glob(&t_envp);
	return (0);
}