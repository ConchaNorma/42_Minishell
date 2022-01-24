# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 19:58:43 by cnorma            #+#    #+#              #
#    Updated: 2022/01/24 21:23:06 by cnorma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

SRC_DIR = ./src/

SRC_FILES =	main.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR = ./obj/

OBJ = $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRC:.c=.o))

HEADER = inc/minishell.h

CC = gcc

FLAGS = -Wall -Wextra -Werror -g

.PHONY: all re clean fclean

all : $(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@ -I $(HEADER)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(OBJ) -lreadline -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJ) $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
