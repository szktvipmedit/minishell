CC			= cc
CFLAGS	= -Wall -Wextra -Werror
LFLAGS	= -L ./libft -lft

SRCS		= minishell.c

OBJS		= $(SRCS:.c=.o)
LIBFT		= ./libft/libft.a
HEADER	= minishell.h
NAME		= minishell

all:			$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
					$(CC) $(CFLAGS) $(LFLAGS) $(SRCS) -o $(NAME)

$(LIBFT):	
					@make -C ./libft/

%.o:			%.c $(HEADER)
					$(CC) $(CFLAGS) -c $< -o $@

clean:
					@make clean -C ./libft/
					rm -rf $(OBJS)

fclean:		clean
					@make fclean -C ./libft/
					rm -rf $(NAME)

re:				fclean all

.PHONY:		all clean fclean re