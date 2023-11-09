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

#define WORD 0
#define OPERATOR 1

#define INPUT 1
#define OUTPUT 2
#define HEREDOC 3
#define APPEND 4

#define ERROR_INPUT 1
//error_message
#define STDERR 2
#define ERROR_SHORTAGE "-minishell: syntax error near unexpected token `newline'\n"
#define ERROR_OPEN "failed open\n"

typedef struct s_token
{
	char					*word;
	int type; // word or operatior or eof
	struct s_token			*next;
}							t_token;

typedef struct s_redirect_node
{
    pid_t                   pid;
    char                    *target_filename;
    char                    *cmd_args; //[option]や[不明な指定(INPUT policy参照)]含む
    char **split_cmd_args;
    char *cmd_path;
    char                    *limiter;
    int                     target_fd;
    int                     operator_idx;
    int                     pipe_fd[2];
}							t_redirect_node;

typedef struct s_node
{
	int type; // INPUT 1 or OUTPUT 2 or HEREDOC 3 or APPEND 4
	t_token					*args;
	struct s_node			*next;
	struct s_node			*prev;
	t_redirect_node	*redirect;
}							t_node;

typedef struct s_env_info
{
    char  *path_addr;
    char **paths;
} t_env_info;

//clear.c
void redirect_node_clear(t_redirect_node *redirect);
void parent_clear(t_redirect_node *redirect);

//get_file.c
void  get_infile(t_node *parse_node);
void get_outfile(t_redirect_node *redirect);
//error.c
// int redirection_args_check(t_node *parse_node);
void error_message(char *error_message);

// child.c
void child(t_node *parse_node, t_env_info env_info, char **envp);

//redirection.c
void get_paths(t_env_info *env_info, char **envp);
void redirection(t_node parse_node, t_env_info env_info, char **envp);

#endif