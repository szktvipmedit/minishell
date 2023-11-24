#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum	s_type 
{
	//signal_type
	SHELL_LOOP,

	//token_type
	WORD,
	REDIRECT,
	PIPE,

	//redirect_type
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

typedef struct	s_redirect {
	char					*target_name;//char *file_nameにするとdelimiterに違和感出るため
	t_type				type;
}								t_redirect;

typedef struct	s_node
{
	size_t				args_count;
	char					**args;//この形にすることで、実装も楽だし後でexecveの引数にそのまま渡せる(environ_list_headも同様)

	size_t				redirects_count;
	t_redirect		*redirects;//上限がだいたい分かっているので線形リストではなく構造体の配列
	
	char					*temp_file;//各nodeの最後に更新されたheredoc隠しファイル

	pid_t					pid;
	int						pipe_fd[2];
	//pidとpipe_fdは、一気にパイプの数分mallocしてその配列をt_shellで持つのではなく、各ノードで管理しその都度代入、closeする。
}								t_node;

typedef struct	s_shell
{
	char					**environ_list_head; //この形にすることで、実装も楽だし後でexecveの引数にそのまま渡せる(argsも同様)
	char					*line;
	t_token				*token_head;
	int						tokenize_error;
	size_t				node_count;
	t_node				*node_head;
}								t_shell;

volatile sig_atomic_t	g_exit_status;

// exit.c
void	ft_free_all_and_exit(t_shell *shell);
void	ft_msg_and_exit();

// signal.c
void	ft_set_signal_handler(t_type type);
void	ft_display_new_prompt(int sig);

// shell_loop.c
void	ft_shell_loop(t_shell *shell);

// tokenize.c
t_token	*ft_tokenize(char *line, t_shell *shell);
t_token	*ft_new_token(char *word, t_type type, t_shell *shell);

// tokenize_utils_1.c
t_token	*ft_add_operator_token(char **resume, char *line, t_shell *shell);

// tokenize_utils_2.c
t_token	*ft_add_word_token(char **resume, char *line, t_shell *shell);

// syntax.c
int	ft_check_syntax(t_token	**token);

// parse.c
t_node	*ft_parse(t_token **token, t_shell *shell);

// parse_utils.c
t_token			*ft_shift_node_location(t_token **token, size_t i);
size_t			ft_count_args(t_token **node_head);
char				**ft_create_args(t_token **node_head, size_t args_count, t_shell *shell);
size_t			ft_count_redirect(t_token **node_head);
t_redirect	*ft_create_redirects(t_token **node_head, size_t redirects_count, t_shell *shell);

// expand.c
void	ft_expand(t_node *node, t_shell *shell);

// expand_utils_1.c
void	ft_dollar_to_environ(char **old_word, char **new_word, t_shell *shell);

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

// exec_cmd.c
void	ft_execute_command(char **args, char **environ_list_head);

// exec_redirects.c
void	ft_prepare_redirects(t_node	node, t_shell *shell);

// exec_multiple.c 
void	ft_exec_multiple_nodes(t_node	*node, t_shell *shell);

// exec_multiple_utils.c
void	ft_exec_multiple_child(t_node	*node, size_t node_index, t_shell *shell);

// free.c
void	ft_free_node(t_node *node, t_shell *shell);
void	ft_free_token(t_token *token);
void	ft_free_strs(char **strs);

#endif