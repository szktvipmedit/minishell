#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <sys/ioctl.h>

# define WITHOUT_EXIT -1

typedef enum	s_type 
{
	//signal_type
	SHELL_LOOP,
	HEREDOC,
	PARENT_PROCESS,
	CHILD_PROCESS,

	//token_type
	WORD,
	REDIRECT,
	PIPE,

	//redirect_target_type
	INPUTFILE,
	OUTPUTFILE,
	DELIMITER,
	APPENDFILE,
}	t_type;

typedef struct		s_token
{
	char						*word;
	t_type					type;
	struct s_token	*next;
}									t_token;

typedef struct	s_redirect
{
	char					*target_name;
	t_type				type;
}								t_redirect;

typedef struct	s_node
{
	size_t				args_count;
	char					**args;

	size_t				redirects_count;
	t_redirect		*redirects;
	
	char					*temp_file;
	int						delimiter_with_quote;

	pid_t					pid;
	int						pipe_fd[2];
}								t_node;

typedef struct	s_shell
{
	char					**environ_list_head;
	char					*line;
	t_token				*token_head;
	int						tokenize_error;
	size_t				node_count;
	t_node				*node_head;
	int						heredoc_error;
	char					*expand_free_list[6];
	int						std_fd[2];//builtinを親プロセスで実行した後、stdinとstdoutのfdを元の状態に戻すために保管しておく。
	int						is_single_node_builtin;//このケースだけは、forkを実行しないため、いろいろと例外が発生する。
	int						single_node_builtin_error;
}								t_shell;

volatile sig_atomic_t	g_exit_status;

// exit.c
void	ft_free_all_and_exit(t_shell *shell, int exit_type);
void	ft_msg_and_exit();
void	ft_delete_heredoc_file(t_node *node, t_shell *shell);

// signal.c
void	ft_set_signal_handler(t_type type);

// shell_loop.c
void	ft_shell_loop(t_shell *shell);

// tokenize.c
void		ft_tokenize(char *line, t_shell *shell);
t_token	*ft_new_token(char *word, t_type type, t_shell *shell);

// tokenize_utils_1.c
t_token	*ft_add_operator_token(char **line, t_shell *shell);

// tokenize_utils_2.c
t_token	*ft_add_word_token(char **line, t_shell *shell);

// syntax.c
int	ft_check_syntax(t_token	*token);

// parse.c
void	ft_parse(t_token *token, t_shell *shell);

// parse_utils.c
t_token			*ft_shift_node_location(t_token *token, size_t i);
size_t			ft_count_args(t_token **node_head);
char				**ft_create_args(t_token **node_head, size_t args_count, t_shell *shell);
size_t			ft_count_redirect(t_token **node_head);
t_redirect	*ft_create_redirects(t_token **node_head, size_t redirects_count, t_shell *shell);

// expand.c
void	ft_expand(t_node *node, t_shell *shell);

// expand_utils_1.c
void	ft_dollar_to_environ(char **old_word, char **new_word, t_shell *shell);
void	ft_reset_expand_free_list(char **list);

// expand_utils_2.c
void	ft_append_char(char **new_word, char c, t_shell *shell);
void	ft_remove_delimiter_quotes(char **old_word, char **new_word, char quote_type, t_shell *shell);
void	ft_remove_quotes(char **old_word, char **new_word, char quote_type, t_shell *shell);
int		ft_create_src_variable(char **old_word, char **src, t_shell *shell);

// heredoc.c
void	ft_heredoc(t_node *node, t_shell *shell);

// execute.c
void	ft_execute(t_node	*node, t_shell *shell);

// execute_utils.c
void	ft_exec_child(t_node node, t_shell *shell);
void	ft_set_exit_status(int status);
bool	ft_is_builtin(char *arg);

// exec_cmd.c
void	ft_exec_path_cmd(char **args, char **environ_list_head, t_shell *shell);

// exec_redirects.c
void	ft_prepare_redirects(t_node	node, t_shell *shell);

// exec_multiple.c 
void	ft_exec_multiple_nodes(t_node	*node, t_shell *shell);

// exec_multiple_utils.c
void	ft_exec_multiple_child(t_node	*node, size_t node_index, t_shell *shell);

// free.c
void	ft_free_strs(char **strs);
void	ft_free_token(t_token *token);
void	ft_free_redirects(t_redirect *redirects, size_t redirects_count);
void	ft_free_node(t_node *node, t_shell *shell);

// exec_builtin.c
void	ft_exec_builtin(t_node node, t_shell *shell);

// shlvl.c
void	ft_increment_shlvl(t_shell *shell);

// builtin/ft_echo.c
void	ft_echo(char **args);

// builtin/ft_exit.c
void	ft_exit(char **args, t_shell *shell);

// builtin/ft_env.c
void	ft_env(char **args, t_shell *shell);

// builtin/ft_pwd.c
void	ft_pwd(t_shell *shell);

#endif