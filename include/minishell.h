/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:58:00 by tchartie          #+#    #+#             */
/*   Updated: 2024/06/18 22:31:45 by tchartie         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>

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
/*                t_cmd struct                */
/*     Prototype for t_cmd struct fonction    */
/* ****************************************** */
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void	ft_lstadd_front_cmd(t_cmd **lst, t_cmd *new);
void	ft_lstclear_cmd(t_cmd **lst);
void	ft_lstdelone_cmd(t_cmd *lst);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
t_cmd	*ft_lstnew_cmd(char *arg, int type, int index);
t_cmd	*ft_lstnmap_cmd(t_cmd *cmd, int npipe);
t_cmd	*ft_cmd_creation(char *arg, int index, t_cmd *linked_list);
int     ft_find_type(char *arg, t_cmd *prev);

t_cmd	*ft_cmd_creation(char *arg, int index, t_cmd *linked_list);
int     ft_find_type(char *arg, t_cmd *prev);

void	ft_lstadd_back_glob(t_glob **lst, t_glob *new);
void	ft_lstadd_front_glob(t_glob **lst, t_glob *new);
void	ft_lstclear_glob(t_glob **lst);
void	ft_lstdelone_glob(t_glob *lst);
t_glob	*ft_lstlast_glob(t_glob *lst);
t_glob	*ft_lstnew_glob(char *name, int equal, char *content);
t_glob  *ft_globsolo_creation(char *arg);
void   ft_lstadd_back_alpha_envp(t_glob **list, t_glob *new);
int     ft_name_len(char *tmp);

/* ****************************************** */
/*                   Expand                   */
/*       Prototype for expand fonction        */
/* ****************************************** */
void    ft_expand(t_cmd **list, t_glob *t_envp);
int     ft_verif_main(char *arg);
void	ft_expand_modif_main(t_cmd *list, t_glob *t_envp);
t_cmd	*expand_tokenizer(t_input *cmd);

/* ****************************************** */
/*                Builtins                	  */
/*    Prototype for builtins's main fonction  */
/* ****************************************** */
int		ft_echo(int fd, t_cmd *cmd);
char	*ft_pwd(void);
int		ft_env(int fd, t_glob **envp);
int		ft_unset(t_glob **envp, t_cmd *args);
int		ft_export(int fd, t_glob **t_envp, t_cmd *args);
int     ft_check_quote_and_delete(t_cmd **t_args);
int		ft_cd(t_cmd *cmd);
int		ft_exit(int fd, t_cmd *cmd);

/* ****************************************** */
/*                  Parser                    */
/*       Prototype for Parser fonction        */
/* ****************************************** */
int     prompt(t_glob *t_envp);
char	**lexer(char *input, t_glob *t_envp);
void	tokenizer(t_input *cmd, t_glob *t_envp);
void	handle_quote(t_cmd *start);

/* ****************************************** */
/*                 Execution                  */
/*      Prototype for execution fonction      */
/* ****************************************** */
int     ft_execution_main(t_glob **t_envp, t_cmd *cmd);
// int     ft_start_execution(int fd, t_glob **t_envp, t_cmd *cmd, int npipe);
int     ft_execute_other_cmd(t_glob **t_envp, t_cmd *cmd);
int     ft_find_builtins_part1(int fd, t_glob **t_envp, t_cmd *cmd);
// int     ft_execution_pipe_main(t_glob **t_envp, t_cmd *cmd, int len_pipe);
int     ft_here_doc(t_glob **t_list, t_cmd *cmd);
int     ft_append_redir(t_glob **t_envp, t_cmd *cmd);
int	    ft_trunc_redir(t_glob **t_envp, t_cmd *cmd);
int	ft_execution_cmd(int fd, t_glob **t_envp, t_cmd *cmd);

/* ****************************************** */
/*             Execution utils                */
/*   Prototype for execution utils fonction   */
/* ****************************************** */
int     ft_pipe_len(t_cmd *cmd);
int     ft_have_heredoc(t_cmd *cmd);
int	    ft_tab_len(char	**tab);
int     ft_glob_len(t_glob *tmp);
void	ft_clear_tab(char	**tmp);
void	ft_clear_argvs(char ***argvs);

char	*ft_expand_line(t_glob **t_list, char *line);

t_bool	is_white_space(char *str, int i);
t_bool	is_special_char(char *str, int i);
t_bool	is_redirection(t_input *cmd, t_token *token);
void	grab_token(t_input *cmd, t_token *token);

int     have_call_function(char *line);
char	*create_file(int *tmp_fd);
char	*ft_call_function_main(char *line, t_glob **t_envp);
int	have_call_function(char *line);
int	ft_get_end_call_function(char *line);

#endif //MINISHELL_H
