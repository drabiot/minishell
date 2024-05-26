/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:58:00 by tchartie          #+#    #+#             */
/*   Updated: 2024/05/26 16:11:22 by nberduck         ###   ########.fr       */
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

typedef struct s_cmd
{
	char            *arg;
    int             type;
    unsigned int    index;
    struct s_cmd    *next;
}			        t_cmd;

typedef struct s_cwd
{
	char	*relative_path;
	char	*absolute_path;
}			t_cwd;

typedef struct s_glob
{
    char                *name;
    int                 equal;
    char                *content;
    struct s_glob    *next;
}                       t_glob;

/* ****************************************** */
/*                Global                	  */
/*    Prototype for Global's utils fonction   */
/* ****************************************** */
void	ft_lstadd_back_glob(t_glob **lst, t_glob *new);
void	ft_lstadd_front_glob(t_glob **lst, t_glob *new);
void	ft_lstclear_glob(t_glob **lst);
void	ft_lstdelone_glob(t_glob *lst);
t_glob	*ft_lstlast_glob(t_glob *lst);
t_glob	*ft_lstnew_glob(char *arg, int type, char *content);

/* ****************************************** */
/*                Builtins                	  */
/*    Prototype for builtins's main fonction  */
/* ****************************************** */
int		ft_echo(int fd, char *str, int option);
char	*ft_pwd(void);
int		ft_env(char **envp);
int		ft_unset(t_list **envp, char **args);
int		ft_export(t_glob **t_envp, t_cmd *args);
int		ft_cd(char *path);
int		ft_exit(int	exit);

/* ****************************************** */
/*                Builtins utils              */
/*Prototype for builtins utils's main fonction*/
/* ****************************************** */
t_glob	*split_args(char **args);
int     ft_check_quote_and_delete(t_cmd **t_args);

int prompt(t_glob *t_envp);
char	**lexer(char *input, t_glob *t_envp);
void	tokenizer(t_input *cmd, t_glob *t_envp);

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void	ft_lstadd_front_cmd(t_cmd **lst, t_cmd *new);
void	ft_lstclear_cmd(t_cmd **lst);
void	ft_lstdelone_cmd(t_cmd *lst);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
t_cmd	*ft_lstnew_cmd(char *arg, int type, int index);

t_cmd	*ft_cmd_creation(char *arg, int index, t_cmd *linked_list);
int     ft_find_type(char *arg, t_cmd *prev);

void ft_expand(t_cmd **list, t_glob *t_envp);
int ft_verif_main(char *arg);
void	ft_expand_modif_main(t_cmd *main, t_cmd *list, t_glob *t_envp);
void	expand_split(t_cmd *list, t_cmd *before, char *content);
t_cmd	*expand_tokenizer(t_input *cmd);

t_glob  *ft_envp_creation(char **envp);
t_glob  *ft_globsolo_creation(char *envp);
int     ft_name_len(char *tmp);

// 
// 
// builtins/ft_utils_builtins.c \
// builtins/ft_echo.c \
// builtins/ft_pwd.c \
// builtins/ft_env.c \
// builtins/ft_unset.c \
// builtins/ft_cd.c \
// builtins/ft_exit.c 
#endif //MINISHELL_H
