# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 19:58:43 by cnorma            #+#    #+#              #
#    Updated: 2022/03/29 00:03:57 by cnorma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_LIB		=	./libft
LIBFT		=	libft.a

SRC_RL		=	./readline
RL			=	readline history

NAME 		=	minishell

SRC_DIR		=	./src/

SRC_FILES	=	main.c				preparser.c 				parser.c	\
				executer.c			redirection.c				builtin.c	\
				builtin_cd.c		builtin_cd_getpath.c		builtin_export.c	utils.c		\
				builtin_unset.c		utils_free_exit.c			parser_dollar.c \
				parser_redirect.c	parser_cmd_pipe.c			signals.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR		=	./obj/

OBJ			=	$(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRC:.c=.o))

HEADER		=	inc/minishell.h

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror -g


all:			$(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(HEADER)
				$(CC) $(FLAGS) -c $< -o $@ -I inc/ -I${SRC_RL}

$(NAME):		$(OBJ) $(HEADER)
				@$(MAKE) -C $(SRC_LIB)
				@$(MAKE) static -C ${SRC_RL}
				$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(SRC_LIB)/$(LIBFT) -L${SRC_RL} ${addprefix -l,${RL}} -ltermcap

$(OBJ_DIR):
				@mkdir -p $@

clean:
				$(MAKE) clean -C $(SRC_LIB)
				@rm -rf $(OBJ) $(OBJ_DIR)
				@make clean -C ${SRC_RL}

fclean:			clean
				@rm -f $(NAME) $(SRC_LIB)/$(LIBFT)

re:				fclean all

.PHONY:			all re clean fclean
