SRCS = srcs/redirection/test.c \
	   srcs/redirection/child.c \
	   srcs/redirection/clear.c \
	   srcs/redirection/error.c \
	   srcs/redirection/get_file.c \
	   srcs/redirection/redirect_input.c \
	   srcs/redirection/redirection.c \
	#    .c \


OBJS = ${patsubst $(SRCS_DIR)%.c,  $(OBJS_DIR)%.o, $(SRCS)}

NAME = minishell
SRCS_DIR = srcs/redirection/
OBJS_DIR = objs/
INCS_DIR = incs/
LIBFT_DIR = libft/

LIBFT = ${LIBFT_DIR}/libft.a

CC = cc
# CFLAGS = -Wall -Wextra -Werror -g
CFLAGS = -g

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

