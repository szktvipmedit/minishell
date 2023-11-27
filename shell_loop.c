#include "minishell.h"

static void	ft_readline_error(t_shell *shell)//本家によせて"exit"と表示してからexit。
{
	ft_free_strs(shell->environ_list_head);
	write(1, "exit\n", 5);
	exit(g_exit_status);//minishellの中でminishellをexitした際の終了ステータスも引き継げるようにする。
}

static void	ft_reset(t_shell *shell)
{
	char	**tmp;

	ft_delete_heredoc_file(shell->node_head, shell);//nodeの情報を使用するため、nodeをfreeするまえに実行。
	free(shell->line);//この時点ではlineがNULLではないことは保証されてる。
	ft_free_token(shell->token_head);
	ft_free_node(shell->node_head, shell);
	tmp = shell->environ_list_head;
	*shell = (t_shell){0};//shell構造体をenviron_list_headを除いて初期化する。
	shell->environ_list_head = tmp;
}

// この関数内で受け取ったlineの全ての処理作業が行われる。
static void	ft_interpret_line(char *line, t_shell *shell)
{
	ft_tokenize(line, shell);
	if (shell->tokenize_error == -1)
		return;
	if (ft_check_syntax(shell->token_head) == -1)
		return;
	ft_parse(shell->token_head, shell);
	ft_expand(shell->node_head, shell);
	ft_heredoc(shell->node_head, shell);//heredocを処理するのはメインプロセスであるためこのタイミング
	if (shell->heredoc_error == -1)
		return;
	ft_execute(shell->node_head, shell);
}

// whileループのみで構成されたminishellプログラムのメイン関数。
// エラーが発生するかシグナルが送られるまでループは終了しない。
void	ft_shell_loop(t_shell *shell)
{
	while (1)
	{
		ft_set_signal_handler(SHELL_LOOP);
		shell->line = readline("minishell$ ");
		if (shell->line == NULL)
			ft_readline_error(shell);
		else if (shell->line[0] == '\0')
			;
		else
		{
			add_history(shell->line);
			ft_interpret_line(shell->line, shell);
		}
		ft_reset(shell);//shell->environ_list_head以外は全て消して初期化
	}
}
