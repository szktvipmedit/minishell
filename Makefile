SRCS = main.c \


OBJS = ${patsubst $(SRCS_DIR)%.c,  $(OBJS_DIR)%.o, $(SRCS)}

NAME = minishell
SRCS_DIR = srcs/
OBJS_DIR = objs/
INCS_DIR = incs/
LIBFT_DIR = libft/

LIBFT = ${LIBFT_DIR}/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	mkdir -p ${@D}
	${CC} ${CFLAGS} -I {INCS_DIR} -c $< -o $@ 

${NAME}: ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT}

${LIBFT}:
	make -C ${LIBFT_DIR}

.PHONY: all clean fclean re
all: ${NAME};

clean:
	make fclean -C ${LIBFT_DIR}
	rm -rf objs

fclean: clean
	rm -rf ${NAME}

re: fclean all;

