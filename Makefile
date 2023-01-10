# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 13:30:55 by gpasquet          #+#    #+#              #
#    Updated: 2023/01/10 14:56:13 by gpasquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

CFLAGS = -g -Wall -Wextra -Werror

NAME = pipex

LIBFT = libft/libft.a

SRC =	mandatory/src/pipex.c \
		mandatory/src/utils.c \
		mandatory/src/parsing.c \
		mandatory/src/free_functions.c \
		mandatory/src/struct_utils.c \
		mandatory/src/child_functions.c \
		mandatory/src/error_functions.c

BONUS = bonus/src/pipex_bonus.c \
		bonus/src/utils_bonus.c \
		bonus/src/parsing_bonus.c \
		bonus/src/free_functions_bonus.c \
		bonus/src/struct_utils_bonus.c \
		bonus/src/child_functions_bonus.c \
		bonus/src/error_functions.c \
		bonus/src/heredoc_functions.c \

OBJS = ${SRC:.c=.o}

OBJS_BONUS = ${BONUS:.c=.o}

.c.o:
	${CC} ${CFLAGS}  -c $< -o ${<:.c=.o}

all:	$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

${LIBFT}:
	make -C libft

bonus:	$(LIBFT) $(OBJS_BONUS)
	${CC} ${CFLAGS} ${OBJS_BONUS} ${LIBFT} -o ${NAME}


clean:
	${RM} ${OBJS} ${OBJS_BONUS}
	make clean -C libft

fclean: clean
	${RM} ${NAME}
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
