# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 19:58:43 by cnorma            #+#    #+#              #
#    Updated: 2022/01/25 22:45:19 by aarnell          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell

SRC_DIR		=	./src/

SRC_FILES	=	main.c		parcer.c	executer.c	\


SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR		=	./obj/

OBJ			=	$(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRC:.c=.o))

HEADER		=	inc/minishell.h

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror -g

.PHONY:			all re clean fclean

all:			$(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(HEADER)
				$(CC) $(FLAGS) -c $< -o $@ -I inc/

$(NAME):		$(OBJ) $(HEADER)
				$(CC) $(FLAGS) $(OBJ) -lreadline -o $(NAME)

$(OBJ_DIR):
				@mkdir -p $@

clean:
				@rm -rf $(OBJ) $(OBJ_DIR)

fclean:			clean
				@rm -f $(NAME)

re:				fclean all
