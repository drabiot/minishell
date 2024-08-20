# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 18:00:04 by tchartie          #+#    #+#              #
#    Updated: 2024/08/20 19:05:37 by adorlac          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#============ NAME ============#

NAME		=		minishell

#========= COMPILATOR =========#

CC			=		clang

#=========== FLAGS ============#

CFLAGS		=		-Wall -Wextra -Werror	#Usual flags
GFLAGS		=		$(CFLAGS) -g #-fsanitize=address		#Flag for gdb or valgrind

#=========== COLOR ============#

BASE_COLOR 	=		\033[0;39m
GRAY 		=		\033[0;90m
RED 		=		\033[0;91m
GREEN 		=		\033[0;92m
YELLOW 		=		\033[0;93m
BLUE 		=		\033[0;94m
MAGENTA		=		\033[0;95m
CYAN 		=		\033[0;96m
WHITE		=		\033[0;97m

#========== SOURCES ===========#

INCLUDE_DIR	=		include
INCLUDE		=		$(INCLUDE_DIR)/minishell.h

LIBFT_DIR	=		libft

SRCS_DIR	=		src/
OBJS_DIR	=		obj/

SRCS		=		main.c \
					signals.c \
					parser/prompt.c \
					parser/lexer.c \
					parser/tokenizer.c \
					parser/tokenizer_utils.c \
					parser/quote_manager.c \
					parser/error_syntax.c \
					parser/expand/expand_main.c \
					parser/expand/expand_verif.c \
					parser/expand/expand_modif.c \
					parser/expand/expand_modif_utils.c \
					parser/expand/expand_modif_utils_two.c \
					parser/expand/expand_tokenizer.c \
					parser/cmd_creation/cmd_creation.c \
					parser/cmd_creation/ft_find_type.c \
					parser/cmd_creation/ft_find_type_utils.c \
					builtins/ft_export.c \
					builtins/ft_export_handle.c \
					builtins/ft_export_utils.c \
					builtins/ft_export_utils_two.c \
					builtins/ft_echo.c \
					builtins/ft_pwd.c \
					builtins/ft_env.c \
					builtins/ft_unset.c \
					builtins/ft_cd.c \
					builtins/ft_exit.c \
					builtins/ft_exit_utils.c \
					builtins/ft_exit_error.c \
					libft_cmd/ft_lstadd_back_cmd.c \
					libft_cmd/ft_lstadd_front_cmd.c \
					libft_cmd/ft_lstclear_cmd.c \
					libft_cmd/ft_lstdelone_cmd.c \
					libft_cmd/ft_lstlast_cmd.c \
					libft_cmd/ft_lstnew_cmd.c \
					libft_cmd/ft_lstnmap_cmd.c \
					libft_cmd/ft_lstsize_cmd.c \
					libft_glob/ft_lstcreate_glob.c \
					libft_glob/ft_lstadd_back_glob.c \
					libft_glob/ft_lstadd_front_glob.c \
					libft_glob/ft_lstclear_glob.c \
					libft_glob/ft_lstdelone_glob.c \
					libft_glob/ft_lstlast_glob.c \
					libft_glob/ft_lstnew_glob.c \
					libft_glob/ft_lstsize_glob.c \
					execution/execution_main.c \
					execution/execution_main_utils.c \
					execution/execution_init.c \
					execution/execution_init_utils.c \
					execution/execution_lst.c \
					execution/execution_access.c \
					execution/execution_redir.c \
					execution/execution_process.c \
					execution/execution_process_utils.c \
					execution/execution_builtins.c \
					execution/execution_utils.c \
					execution/execution_error.c \
					execution/execution_heredoc.c \
					execution/execution_heredoc_utils.c \
					execution/execution_end.c


OBJS		=		$(SRCS:.c=.o)

SRCS_F		=		$(addprefix $(SRCS_DIR),$(SRCS))

OBJS_F		=		$(addprefix $(OBJS_DIR),$(OBJS))

#========= EXECUTABLE =========#

all :				$(NAME)

makelibft :
					@make -C $(LIBFT_DIR) all --no-print-directory

$(NAME) :			$(OBJS_F) | makelibft
					@$(CC) $(OBJS_F) -o $(NAME) -Llibft -lft -lreadline -I$(INCLUDE_DIR)
					@echo "$(GREEN)Minishell successfully compiled! $(BASE_COLOR)"

$(OBJS_DIR)%.o :	$(SRCS_DIR)%.c $(INCLUDE)
					@mkdir -p $(OBJS_DIR)
					@mkdir -p obj/parser
					@mkdir -p obj/parser/cmd_creation
					@mkdir -p obj/parser/expand
					@mkdir -p obj/builtins
					@mkdir -p obj/libft_cmd
					@mkdir -p obj/libft_glob
					@mkdir -p obj/execution
					@echo "$(YELLOW)Compiling: $< $(BASE_COLOR)"
					@$(CC) $(GFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean :
					@rm -rf $(OBJS_DIR)
					@make -C $(LIBFT_DIR) clean --no-print-directory
					@echo "$(BLUE)Minishell objects files cleanned! $(BASE_COLOR)"

fclean :
					@rm -rf $(OBJS_DIR)
					@echo "$(BLUE)Minishell objects files cleanned! $(BASE_COLOR)"
					@rm -rf $(NAME)
					@echo "$(CYAN)Minishell executable file cleanned! $(BASE_COLOR)"
					@make -C $(LIBFT_DIR) fclean --no-print-directory

re :				fclean all

.PHONY :			all makelibft clean fclean re
