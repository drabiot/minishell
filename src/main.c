/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:54:59 by tchartie          #+#    #+#             */
/*   Updated: 2024/03/20 17:51:58 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_list  *ft_envp_creation(char **envp)
{
	t_list			*list;
	t_list			*tmp;
	unsigned int	i;

	i = 0 ;
   list = NULL;
	while (envp[i])
	{
		tmp = ft_lstnew(ft_strdup(envp[i]));
		ft_lstadd_back(&list, tmp);
      i++;
	}
   return (list);
}

static void ft_envp_print(t_list *t_envp)
{
   int   i;
   
   i = 0;
   t_list *tmp;

   tmp = t_envp;
   while (tmp)
   {
      printf("%s\n", (char *)tmp->content);
      printf("%i\n", i);
      tmp = tmp->next;
      i++;
   }
}

int main(int argc, char **argv, char **envp)
{
   t_list *t_envp;
   // int  ret;

   // (void)argc;
   // (void)argv;
   // (void)envp;
   // ret = prompt();
   // return (ret);
   
   (void)argc;
   // (void)envp;
   // (void)argv;

   t_envp = ft_envp_creation(envp);
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

   ft_exit(ft_atoi(argv[1]));
   
   ft_envp_print(NULL);
   ft_lstclear(&t_envp, free);
   return (0);
}