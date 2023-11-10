#include "minishell.h"

void	ft_free_shell(t_shell *shell)
{
	// shell->environ_list_headとかmalloc系全部フリーする
}



// 本家bashのexit表記を再現。
void	ft_readline_error(t_shell *shell)
{
	ft_free_shell(shell);
	write(1, "exit\n", 5);
	exit(1);
}
