# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 18:00:04 by tchartie          #+#    #+#              #
#    Updated: 2024/04/06 17:46:34 by nberduck         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#============ NAME ============#

NAME		=		minishell

#========= COMPILATOR =========#

CC			=		clang

#=========== FLAGS ============#

CFLAGS		=		-Wall -Wextra -Werror	#Usual flags
GFLAGS		=		$(CFLAGS) -g			#Flag for gdb or valgrind

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
					parser/prompt.c \
					parser/lexer.c \
					parser/tokenizer.c \
					parser/cmd_creation/cmd_creation.c \
					parser/cmd_creation/ft_find_type.c \
					parser/expand/expand_main.c \
					parser/expand/expand_verif.c \
					parser/expand/expand_modif.c \
					parser/expand/expand_split.c \
					parser/expand/expand_tokenizer.c \
					builtins/ft_utils_builtins.c \
					builtins/ft_echo.c \
					builtins/ft_pwd.c \
					builtins/ft_env.c \
					builtins/ft_unset.c \
					builtins/ft_export.c \
					builtins/ft_cd.c \
					builtins/ft_exit.c \
					libft_cmd/ft_lstadd_back_cmd.c \
					libft_cmd/ft_lstadd_front_cmd.c \
					libft_cmd/ft_lstclear_cmd.c \
					libft_cmd/ft_lstdelone_cmd.c \
					libft_cmd/ft_lstlast_cmd.c \
					libft_cmd/ft_lstnew_cmd.c

OBJS		=		$(SRCS:.c=.o)

SRCS_F		=		$(addprefix $(SRCS_DIR),$(SRCS))

OBJS_F		=		$(addprefix $(OBJS_DIR),$(OBJS))

#========= EXECUTABLE =========#

all :				$(NAME)

makelibft :
					@make -C $(LIBFT_DIR) all --no-print-directory

$(NAME) :			$(OBJS_F) | makelibft
					@$(CC) $(OBJS_F) -o $(NAME) -Llibft -lft -lreadline -I$(INCLUDE_DIR)
					@echo "$(GREEN)Pipex successfully compiled! $(BASE_COLOR)"

$(OBJS_DIR)%.o :	$(SRCS_DIR)%.c $(INCLUDE)
					@mkdir -p $(OBJS_DIR)
					@mkdir -p obj/parser
					@mkdir -p obj/parser/cmd_creation
					@mkdir -p obj/parser/expand
					@mkdir -p obj/builtins
					@mkdir -p obj/libft_cmd
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
