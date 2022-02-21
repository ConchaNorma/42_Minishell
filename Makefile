# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 19:58:43 by cnorma            #+#    #+#              #
#    Updated: 2022/02/21 21:13:10 by aarnell          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_LIB		=	./libft
LIBFT		=	libft.a

NAME 		=	minishell

SRC_DIR		=	./src/

SRC_FILES	=	main.c			preparser.c 		parser.c	\
				executer.c		redirection.c		builtin.c	\
				builtin_cd.c	builtin_export.c	utils.c		\
				builtin_unset.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR		=	./obj/

OBJ			=	$(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRC:.c=.o))

HEADER		=	inc/minishell.h

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror -g


all:			$(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(HEADER)
				$(CC) $(FLAGS) -c $< -o $@ -I inc/

$(NAME):		$(OBJ) $(HEADER)
				@$(MAKE) -C $(SRC_LIB)
				$(CC) $(FLAGS) $(OBJ) $(SRC_LIB)/$(LIBFT) -lreadline -o $(NAME)

$(OBJ_DIR):
				@mkdir -p $@

clean:
				$(MAKE) clean -C $(SRC_LIB)
				@rm -rf $(OBJ) $(OBJ_DIR)

fclean:			clean
				@rm -f $(NAME) $(SRC_LIB)/$(LIBFT)

re:				fclean all

.PHONY:			all re clean fclean
