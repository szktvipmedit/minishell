#include "minishell.h"

// いったん構造体の全ての変数を0かNULLで初期化。
// もし特定の値で初期化したいなら、その後に代入処理を追加可能。
static void	ft_initialize_shell(t_shell *shell)
{
	*shell = (t_shell){0};
}



// とりあえず必要最低限の二次元マップに環境変数を格納。
// 必要があればハッシュ法を実装するか、連結リスト構造に変える。
static void	ft_clone_environ_list(t_shell *shell)
{
	extern char	**environ;
	char				**tmp;
	size_t			i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (environ[i] != NULL)
	{
		tmp[i] = ft_strdup(environ[i]);
		i++;
	}
	tmp[i] = NULL;
	shell->environ_list_head = tmp;
}



// whileループのみで構成されたminishellプログラムのメイン関数。
// エラーが発生するかシグナルが送られるまでループは終了しない。
static void	ft_shell_loop(t_shell *shell)
{
	char	*line;

	rl_outstream = stderr;
	while (1)
	{
		ft_set_signal_handler(SHELL_LOOP);
		line = readline("minishell$ ");
		if (line == NULL)
			ft_readline_error(shell);
		else if (line[0] == '\0')
			;
		else
		{
			add_history(line);
			ft_interpret_line(line, shell);
		}
		free(line);
	}
}



// 一つの関数に一つの機能を意識して、main関数も余裕をもたせてコンパクトに設計。
// グローバル変数は使わず、構造体t_shellに全て詰め込んで持ち歩く。
// プログラムのメインはft_shell_loop関数。
int	main(int argc, char **argv)
{
	t_shell	shell;
	
	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Usage: ./minishell\n", 2);
		return (1);
	}
	ft_initialize_shell(&shell);
	ft_clone_environ_list(&shell);
	ft_shell_loop(&shell);
	return (0);
}
