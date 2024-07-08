/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:58:00 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/05 11:47:39 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "lexer.h"
# include "type.h"
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

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
int		ft_exit(int exit);

/* ****************************************** */
/*                Builtins utils              */
/*Prototype for builtins utils's main fonction*/
/* ****************************************** */
t_list	*split_args(char **args);

typedef struct s_cmd
{
	char			*arg;
	int				type;
	unsigned int	index;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_cwd
{
	char	*relative_path;
	char	*absolute_path;
}			t_cwd;

int		prompt(t_list *t_envp);
char	**lexer(char *input, t_list *t_envp);
void	tokenizer(t_input *cmd, t_list *t_envp);

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void	ft_lstadd_front_cmd(t_cmd **lst, t_cmd *new);
void	ft_lstclear_cmd(t_cmd **lst);
void	ft_lstdelone_cmd(t_cmd *lst);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
t_cmd	*ft_lstnew_cmd(char *arg, int type, int index);

t_cmd	*ft_cmd_creation(char *arg, int index, t_cmd *linked_list);
int		ft_find_type(char *arg, t_cmd *prev);

void	ft_expand(t_cmd **list, t_list *t_envp);
int		ft_verif_main(char *arg);
void	ft_expand_modif_main(t_cmd *list, t_list *t_envp);

#endif //MINISHELL_H
