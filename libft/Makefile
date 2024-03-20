# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 18:05:50 by tchartie          #+#    #+#              #
#    Updated: 2024/03/19 15:18:02 by nberduck         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#============ NAME ============#

NAME		=		libft.a

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

INCLUDE		=		../include/libft.h

SRCS_DIR	=		src/
OBJS_DIR	=		obj/

SRCS 		= 		ft_isalpha.c \
					ft_isdigit.c \
					ft_isalnum.c \
					ft_isascii.c \
					ft_isprint.c \
					ft_toupper.c \
					ft_tolower.c \
					ft_atoi.c \
					ft_atol.c \
					ft_itoa.c \
					ft_putchar_fd.c \
					ft_putstr_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c \
					ft_lstnew.c \
					ft_lstadd_front.c \
					ft_lstadd_back.c \
					ft_lstsize.c \
					ft_lstlast.c \
					ft_lstdelone.c \
					ft_lstclear.c \
					ft_lstiter.c \
					ft_lstmap.c \
					ft_memset.c \
					ft_bzero.c \
					ft_memcpy.c \
					ft_memmove.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_calloc.c \
					ft_strlen.c \
					ft_strlcpy.c \
					ft_strcat.c \
					ft_strlcat.c \
					ft_strchr.c \
					ft_strrchr.c \
					ft_strcmp.c \
					ft_strncmp.c \
					ft_strnstr.c \
					ft_strdup.c \
					ft_substr.c \
					ft_strjoin.c \
					ft_strnjoin.c \
					ft_strtrim.c \
					ft_split.c \
					ft_strmapi.c \
					ft_striteri.c \
					ft_random.c \

OBJS		=		$(SRCS:.c=.o)

SRCS_F		=		$(addprefix $(SRCS_DIR),$(SRCS))
OBJS_F		=		$(addprefix $(OBJS_DIR),$(OBJS))

#========= EXECUTABLE =========#

all : 				$(NAME)

$(NAME) : 			$(OBJS_F)
					@ar -rcs $(NAME) $(OBJS_F)
					@echo "$(GREEN)Libft successfully compiled! $(BASE_COLOR)"

$(OBJS_DIR)%.o : 	$(SRCS_DIR)%.c $(INCLUDE)
					@mkdir -p $(OBJS_DIR)
					@echo "$(YELLOW)Compiling: $< $(BASE_COLOR)"
					@$(CC) $(CFLAGS) -c $< -o $@

clean :
					@rm -rf $(OBJS_DIR)
					@echo "$(BLUE)Libft objects files cleanned! $(BASE_COLOR)"

fclean :			clean
					@rm -rf $(NAME)
					@echo "$(CYAN)Libft executable file cleanned! $(BASE_COLOR)"

re :				fclean all
					@echo "$(GREEN)Cleanned and rebuild Libft! $(BASE_COLOR)"
	
.PHONY :			all clean fclean re
