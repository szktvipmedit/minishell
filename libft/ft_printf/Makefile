# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: string <string>                            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/24 08:39:12 by kousuzuk          #+#    #+#              #
#    Updated: 2023/07/07 07:59:36 by kousuzuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= src/ft_printf.c \
			  src/ft_generates.c \
			  src/ft_hexaSystem.c \

BONUS		= bonus_src/ft_printf_bonus.c \
			  bonus_src/ft_generates_bonus.c \
			  bonus_src/ft_hexaSystem_bonus.c \

OBJS		= ${SRCS:.c=.o}
BONUS_OBJS	= ${BONUS:.c=.o}

ifdef WITH_BONUS
	SRCS = ${BONUS}
	OBJS = ${BONUS_OBJS}
endif

NAME		= libftprintf.a
RM			= rm -f
AR			= ar rcs
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
BIN_DIR		= bin

%.c%.o:
	${CC} ${CFLAGS} $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make -C libft
			cp libft/libft.a .
			mv libft.a ${NAME}
			${AR} ${NAME} ${OBJS}

.PHONY: all clean fclean re bonus

bonus:	
	make WITH_BONUS=1 ${NAME}

all: ${NAME}

clean:	
	make clean -C libft
	${RM} ${OBJS} ${BONUS_OBJS}

fclean:	clean
	make fclean -C libft
	${RM} ${NAME} libft.a

re:			fclean all ;

	
