#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// #include <.h>

#define INPUT 1
#define OUTPUT 2
#define HEREDOC 3
#define APPEND 4

typedef struct s_token
{
	char					*word;
	int type; // word or operatior
	struct s_token			*next;
}							t_token;

typedef struct s_redirect_node
{
    int                     infile;
    int                     outfile;
    char **paths;
    int pipe_fd[2];
	char					*LIMITER;
	char					*filename;
}							t_redirect_node;

typedef struct s_node
{
	int type; // INPUT 1 or OUTPUT 2 or HEREDOC 3 or APPEND 4
	t_token					*args;
	struct s_node			*next;
	struct s_node			*prev;
	t_redirect_node	*redirect;
}							t_node;

#endif