#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// #include <.h>

# define WORD 0
# define OPERATOR 1

# define COMMAND 0
# define INPUT 1
# define OUTPUT 2
# define HEREDOC 3
# define APPEND 4

# define ERROR_INPUT 1
// error_message
# define STDERR 2
# define ERROR_SHORTAGE "-minishell: syntax error near unexpected token `newline'\n"
# define ERROR_OPEN "failed open\n"

typedef struct s_shell
{
	char			**envp_copy;
	char			*path_addr;
	char			**paths;
}					t_shell;

typedef struct s_token
{
	char			*word;
	int type; // word or operatior or eof
	struct s_token	*next;
}					t_token;

// redirectのたびに必要になる情報
typedef struct s_redirect_node
{
    int             type;// cmd 0 or input 1 or output 2 or heredoc 3 or append 4
	pid_t			pid;

    //INPUT, OUTPUT, APPEND
    char            *target_filename; //redirectionのget_infile()ではなくparserで求めておく。heredocの時はNULLで、代わりにlimiterにその箇所の文字列が入る
	// HEREDOC
	char			*limiter;

	int				operator_idx;
	int				redirect_pipe_fd[2];

	// cmd infomation

    struct s_redirect_node *prev;
    struct s_redirect_node *next;

}					t_redirect_node;

typedef struct s_node
{
    pid_t pid;
	int type; // COMMAND 0 or REDIREDIC 1
	t_token			*args;
	int				infile;
	int				outfile;
	char *cmd_args; //[option]や[不明な指定(INPUT policy参照)]含む
	char			**split_cmd_args;
	char			*cmd_path;

	struct s_node	*next;
	struct s_node	*prev;
	t_redirect_node	*redirect;

}					t_node;

typedef struct s_line
{
	char			*line;
    int             node_cnt;
    int             pipe_cnt;
	int				*pipe_fd;
	t_node			*parse_node;

	/*
	現在見ているparseのidx
	pipe_fd[progress_parse_idx　* 2]がそのparseの読み取りfd,
	pipe_fd[progress_parse_idx　* 2 - 1]がそのparseでの書き込みfd  を指す
	*/
	int				progress_parse_idx;//0はじまり

	// [parse | parse | parse | ]のようなケースでは入力待ち状態に入る
	bool			is_wait_input;
}					t_line;

// clear.c
void				redirect_node_clear(t_redirect_node *redirect);
void				parent_clear(t_node *parse_node);

// get_file.c
void				get_infile(t_node *parse_node);
void				get_outfile(t_node *parse_node);
void				get_infile_case_heredoc(t_redirect_node *redirect);
// error.c
// int redirection_args_check(t_node *parse_node);
void				error_message(char *error_message);

// child.c
void				child(t_node *parse_node, t_shell shell, char **envp,
						int parse_idx);
char				*find_command(char **paths, char *cmd);

// redirection.c
void				get_paths(t_shell *shell, char **envp);
void				redirection(t_line *line, t_node *parse_node,
						t_shell shell);
//redirect_init.c
void redirect_init(t_line *line, t_node *parse_node);

// pipe.c
int					ft_pipe(t_line *line, t_shell shell);

//create_parse_pipes.c
int get_parse_cnt(t_node *node);
void create_pipes(t_line *line, t_node *parse_node);
// int get_pipe_cnt(t_line *line, char *line);

//exec_path
void exec_path(t_line *line, t_node *parse_node, t_shell shell);
#endif