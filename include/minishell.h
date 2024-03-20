/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:58:00 by tchartie          #+#    #+#             */
/*   Updated: 2024/03/20 17:51:06 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>

/* ****************************************** */
/*                Builtins                	  */
/*    Prototype for builtins's main fonction  */
/* ****************************************** */
int		ft_echo(char *str, int option);
char	*ft_pwd(void);
int		ft_env(char **envp);
int		ft_unset(t_list **envp, char **args);
int		ft_export(t_list **t_envp, char **args);
int		ft_cd(char *path);
int		ft_exit(int	exit);
/* ****************************************** */
/*                Builtins utils              */
/*Prototype for builtins utils's main fonction*/
/* ****************************************** */
t_list	*split_args(char **args);

int prompt(void);

#endif //MINISHELL_H