# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 13:30:55 by gpasquet          #+#    #+#              #
#    Updated: 2022/12/20 16:40:44 by gpasquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

CFLAGS = -g -Wall -Wextra -Werror

NAME = pipex

LIBFT = libft/libft.a

SRC =	src/pipex.c \
		src/utils.c \
		src/parsing.c \
		src/free_functions.c \
		src/struct_utils.c \
		src/child_functions.c

OBJS = ${SRC:.c=.o}

.c.o:
	${CC} ${CFLAGS}  -c $< -o ${<:.c=.o}

all:	$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

${LIBFT}:
	make -C libft

clean:
	${RM} ${OBJS}
	make clean -C libft

fclean: clean
	${RM} ${NAME}
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
