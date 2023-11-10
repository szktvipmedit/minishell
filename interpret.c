#include "minishell.h"

// この関数内で受け取ったlineの全ての処理作業が行われる。
それぞれの関数で文法エラー(syntax_error)チェックとset_signal,free_exit処理が必要
void	ft_interpret_line(char *line, t_shell *shell)
{
	tokenize;
	parse;
	expand;(quote_removal, open_heredocとか)
	execution;(single_command or 複数のコマンド(pipex), -> 自作したbuilt_in_command or pathから参照したcommand)
	free_process;(node_listとか全てリセット。lineだけはft_shell_loopでfreeする)
}
