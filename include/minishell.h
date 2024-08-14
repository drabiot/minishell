/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:58:00 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/14 05:47:25 by tchartie         ###   ########.fr       */
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
# include <sys/types.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>

typedef struct s_cmd
{
	char			*arg;
	int				type;
	unsigned int	index;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_cwd
{
	char		*relative_path;
	char		*absolute_path;
	int			return_code;
}				t_cwd;

typedef struct s_exec
{
	int				nb_cmd;
	int				pos_cmd;
	char			*infile;
	char			*outfile[2];
	int				fd_in;
	int				fd_out;
	char			*base_cmd;
	char			*cmd;
	char			**flags;
	bool			have_heredoc;
	char			*limiter;
	bool			file_error;
	bool			is_piped;
	pid_t			pid;
	struct s_exec	*next;
}					t_exec;

typedef struct s_glob
{
	char				*name;
	int					equal;
	char				*content;
	char				**env;
	struct s_glob		*next;
	struct s_cwd		*utils;
}						t_glob;

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
int		ft_find_type(char *arg, t_cmd *prev);
void	expandable_type(t_cmd *exec);

t_cmd	*ft_cmd_creation(char *arg, int index, t_cmd *linked_list);
int		ft_find_type(char *arg, t_cmd *prev);

void	ft_lstadd_back_glob(t_glob **lst, t_glob *new);
void	ft_lstadd_front_glob(t_glob **lst, t_glob *new);
void	ft_lstclear_glob(t_glob **lst);
void	ft_lstdelone_glob(t_glob *lst);
t_glob	*ft_lstlast_glob(t_glob *lst);
t_glob	*ft_lstnew_glob(char *name, int equal, char *content, char **env);
t_glob	*ft_globsolo_creation(char *arg);
t_glob	*ft_envp_creation(char **env);
void	ft_lstadd_back_alpha_envp(t_glob **list, t_glob *new);
int		ft_name_len(char *tmp);

/* ****************************************** */
/*                   Expand                   */
/*       Prototype for expand fonction        */
/* ****************************************** */
void	ft_expand(t_cmd **list, t_glob *t_envp);
int		ft_verif_main(char *arg);
void	ft_expand_modif(t_cmd *cmd, t_glob *t_envp, int type);
t_cmd	*expand_tokenizer(t_input *cmd);

/* ****************************************** */
/*                Builtins                	  */
/*    Prototype for builtins's main fonction  */
/* ****************************************** */
int		ft_echo(int fd, t_exec *exec, t_glob *t_envp);
int		ft_pwd(t_glob *t_envp);
int		ft_env(int fd, t_glob **envp);
int		ft_unset(t_glob **envp, t_exec *exec);
int		ft_export(int fd, t_glob *t_envp, t_exec *exec);
int		ft_check_quote_and_delete(t_exec **exec);
int		ft_cd(t_exec *exec, t_glob **t_envp);
void	ft_exit(int fd, t_exec *exec, t_glob **t_envp, int *return_value);

/* ****************************************** */
/*                  Parser                    */
/*       Prototype for Parser fonction        */
/* ****************************************** */
int		prompt(t_glob *t_envp);
char	**lexer(char *input, t_glob *t_envp);
void	tokenizer(t_input *cmd, t_glob *t_envp);
void	handle_quote(t_cmd *start);
void	add_glob_utils(t_glob *t_envp, t_cwd *utils);
t_bool	is_error_syntax(t_cmd *cmd, t_glob *t_envp, t_input *line);

/* ****************************************** */
/*                 Execution                  */
/*      Prototype for execution fonction      */
/* ****************************************** */
int		ft_execution_main(t_glob **t_envp, t_cmd *cmd);
int		ft_find_builtins(int fd, t_glob **t_envp, t_exec *exec);
int		is_builtins(char *arg);
void	generate_key_random(void);
void    open_heredoc(char *limiter, t_exec *exec);

/* ****************************************** */
/*             Execution utils                */
/*   Prototype for execution utils fonction   */
/* ****************************************** */
int		ft_pipe_len(t_cmd *cmd);
int		ft_have_heredoc(t_cmd *cmd);
int		ft_tab_len(char	**tab);
int		ft_glob_len(t_glob *tmp);

char	*ft_expand_line(t_glob **t_list, char *line);

t_bool	is_white_space(char *str, int i);
t_bool	is_special_char(char *str, int i);
t_bool	is_redirection(t_input *cmd, t_token *token);
void	grab_token(t_input *cmd, t_token *token);

int		have_call_function(char *line);
char	*create_file(int *tmp_fd);

void	ft_errno(void);


void	ft_signal(int sign);
void	free_exit(t_exec *exec, t_glob *t_envp);
void	free_envp(t_glob *t_envp);

#endif //MINISHELL_H
