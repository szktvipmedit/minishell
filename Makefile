CC			= cc
CFLAGS	= -Wall -Wextra -Werror
LFLAGS	= -L ./libft -lft
LDFLAGS = -L $(shell brew --prefix readline)/lib -lreadline
INCLUDE = -I $(shell brew --prefix readline)/include

SRCS		= minishell.c \
					exit.c \
					signal.c \
					shell_loop.c \
					tokenize.c \
					tokenize_utils_1.c \
					tokenize_utils_2.c \
					syntax.c \
					parse.c \
					parse_utils.c \
					expand.c \
					expand_utils_1.c \
					expand_utils_2.c \
					heredoc.c \
					execute.c \
					execute_utils.c \
					exec_path_cmd.c \
					exec_redirects.c \
					exec_multiple.c \
					exec_multiple_utils.c \
					free.c \
					exec_builtin.c \
					shlvl.c \
					builtin/ft_echo.c \
					builtin/ft_exit.c \
					builtin/ft_env.c \
					builtin/ft_pwd.c \
					builtin/ft_export.c \
					builtin/ft_export_utils.c \
					builtin/ft_unset.c \
					builtin/ft_unset_utils.c \
					builtin/ft_cd.c \
					builtin/ft_cd_utils.c \
					builtin/builtin_utils.c \
					minishell_utils.c

OBJS		= $(SRCS:.c=.o)
LIBFT		= ./libft/libft.a
HEADER	= minishell.h
NAME		= minishell

all:			$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
					$(CC) $(CFLAGS) $(LFLAGS) $(LDFLAGS) $(INCLUDE) $(SRCS) -o $(NAME)

$(LIBFT):	
					@make bonus -C ./libft/

%.o:			%.c $(HEADER)
					$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
					@make clean -C ./libft/
					rm -rf $(OBJS)

fclean:		clean
					@make fclean -C ./libft/
					rm -rf $(NAME)

re:				fclean all

.PHONY:		all clean fclean re