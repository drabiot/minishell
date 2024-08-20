/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:58:00 by tchartie          #+#    #+#             */
/*   Updated: 2024/08/20 15:44:24 by tchartie         ###   ########.fr       */
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
#include <sys/stat.h>

/*int	g_return_nbr;*/

typedef struct s_cmd
{
	char			*arg;
	int				type;
	unsigned int	index;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_cwd
{
	char		**env;
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
	char			*name_heredoc[16];
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
int		ft_lstsize_cmd(t_cmd *lst);
int		ft_find_type(char *arg, t_cmd *prev);
void	expandable_type(t_cmd *exec);

t_cmd	*ft_cmd_creation(char *arg, int index, t_cmd *linked_list);
int		ft_find_type(char *arg, t_cmd *prev);

void	ft_lstadd_back_glob(t_glob **lst, t_glob *new);
void	ft_lstadd_front_glob(t_glob **lst, t_glob *new);
void	ft_lstclear_glob(t_glob **lst);
void	ft_lstdelone_glob(t_glob *lst);
t_glob	*ft_lstlast_glob(t_glob *lst);
t_glob	*ft_lstnew_glob(char *name, int equal, char *content);
int		ft_lstsize_glob(t_glob *glob);
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
void	ft_expand_modif(t_cmd *cmd, t_glob *t_envp, int type, int i);
t_cmd	*expand_tokenizer(t_input *cmd);

/* ****************************************** */
/*                Builtins                	  */
/*    Prototype for builtins's main fonction  */
/* ****************************************** */
int		ft_echo(int fd, t_exec *exec, t_glob *t_envp);
int		ft_pwd(t_glob *t_envp);
int		ft_env(int fd, t_glob **envp);
void	create_env(t_glob **t_envp);
int		ft_unset(t_glob **envp, t_exec *exec);
int		ft_export(int fd, t_glob *t_envp, t_exec *exec);
int		ft_check_quote_and_delete(t_exec **exec);
int		ft_cd(t_exec *exec, t_glob **t_envp);
void	ft_exit(t_exec *exec, t_glob **t_envp, int *return_value);

/* ****************************************** */
/*                  Parser                    */
/*       Prototype for Parser fonction        */
/* ****************************************** */
int		prompt(t_glob *t_envp);
char	**lexer(char *input, t_glob *t_envp);
void	tokenizer(t_input *cmd, t_glob *t_envp, unsigned int index);
void	handle_quote(t_cmd *start);
void	add_glob_utils(t_glob *t_envp, t_cwd *utils);
t_bool	is_error_syntax(t_cmd *cmd, t_glob *t_envp, t_input *line);
void	free_t_cmd(t_cmd *cmd);

char	*ft_getenv(char *name, t_glob *t_envp, int i);
void	split_full(char *full, t_cmd *list);
char	**ft_define_split(char *full);
void	add_new_node(t_cmd **list, char *argument, char *next_arg);

void	free_expand_do(char *a, char *b, char *c, char *d);
void	free_char(char **c);
void	ft_expd_do(t_cmd *list, char *content, int start, int end);

/* ****************************************** */
/*                 Execution                  */
/*      Prototype for execution fonction      */
/* ****************************************** */
int		ft_execution_main(t_glob **t_envp, t_cmd *cmd);
int		ft_find_builtins(int fd, t_glob **t_envp, t_exec *exec);
int		is_builtins(char *arg);
void	generate_key_random(void);
void	open_heredoc(char *limiter, t_exec *exec);

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
t_bool	check_file(char **file_limit, char **file, int *file_fd, char *limiter);
void	destroy_tmp(t_exec **exec);
void	free_tmp(t_exec **exec);

void	ft_errno(void);

void	ft_signal(int sign);
void	free_exit(t_exec *exec, t_glob *t_envp);
void	free_envp(t_glob *t_envp);
void	free_utils(t_cwd *utils);
void	ft_env_print_one(int fd, t_glob *tmp);
int		ft_export_state(t_exec *exec, t_glob *t_envp, t_glob *tmp, int state);
int		is_start(t_cmd *prev);
t_bool	is_white_space(char *str, int i);
int		ft_verif_arg_start(char *flg, t_bool err, t_glob *t_envp);
void	change_glob_one(t_glob *list, char *name, char *content);
void	change_glob_two(t_glob *list, char *name, char *content, char *tmp_con);
int		change_glob_sign(char *glob, int start_content);

void	free_exit_tmp_exec(t_exec *tmp_exec);
void	free_exit_envp(t_glob *t_envp);

int		handle_state(t_glob **t_envp, t_exec *exec, int state, int i);
t_bool	no_glob(t_glob **t_envp, char *glob);
void	change_glob(t_glob **t_envp, char *glob, int type, int i);

t_bool	check_limits(const char *num, const char *limit, int i, int j);
int		calculate_exit_code(int exit_code);
void	handle_exit_error(t_glob *t_envp, t_exec *exec, int *exit_code);
void	handle_error(int *exit_code, t_glob *envp, t_exec *exec);
void	handle_exit(t_glob *t_envp, t_exec *exec, int *exit_code);

/* Init */
void	set_base_exec(t_exec *current_node, int nb_cmd, int pos_cmd);
t_exec	*init_exec(t_cmd *cmd, t_glob *t_envp, int len);
t_exec	*append_node(t_glob *glob, t_cmd *cmd, int nb_cmd, int pos_cmd);

t_exec	*ft_last_node(t_exec *lst);
void	ft_add_back(t_exec **lst, t_exec *new);
void	check_node(t_cmd *cmd, t_glob *t_envp, t_exec *list, t_exec *nd);

/* Process */
void	process(t_exec *exec, t_exec *list, t_glob **t_envp);
void	close_fds(t_exec *list);
void	init_process(t_exec *list, t_exec *exec, t_glob **t_envp);

/* Access */
char	*grab_redir(t_cmd *cmd, t_exec *node, int type, int file, t_glob *glob);
char	**get_flags(t_cmd *cmd, char *path);
char	*get_cmd(char *arg, t_glob *glob);
char	*get_cor_path(char *cmd, char *content_path, t_bool is_path, int i);

void	free_paths(char **path);
void	free_exec(t_exec *exec);

#endif //MINISHELL_H
