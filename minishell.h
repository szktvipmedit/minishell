#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

# define SHELL_LOOP 0

typedef struct	s_shell
{
	char					**environ_list_head;
}								t_shell;

volatile sig_atomic_t	g_exit_status;

#endif