#include "minishell.h"

// 課題PDFの要件に従い、ハンドラー関数内でのみ一つだけvolatile sig_atomic_t型のグローバル変数を使用する。
static void	ft_handler_sigint_in_heredoc(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");//これは人が物理的にreturnキーを押す動作を再現してくれる
	rl_on_new_line();
	g_exit_status = 130;
}

static void	ft_handler_display_new_prompt(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();// これでminishell$ というプロンプトが表示される(=readline)
	rl_replace_line("", 0);// これで過去の入力値が出力される現象を防げる。
	rl_redisplay();// これでプロンプトを再表示させる。これ単体だとプロンプトの文字列が空白になる。
	g_exit_status = 130;
}

// シグナルが送られたタイミングによってハンドラー関数を変える必要があるため、
// 引数のtypeの値にセットするタイミングを格納してifで場合分けする。
void	ft_set_signal_handler(t_type type)
{
	if (type == SHELL_LOOP)
	{
		signal(SIGQUIT, SIG_IGN);//このタイミングでの<ctrl-\>はdoes nothing.と課題PDFにあるので、SIG_IGNする。
		signal(SIGINT, ft_handler_display_new_prompt);//ctrl+C == SIGINT
	}
	if (type == HEREDOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_handler_sigint_in_heredoc);
	}
	if (type == PARENT_PROCESS)//親プロセスは子プロセスやexecuteの実行を邪魔する可能性のあるシグナルを全て無視する
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
	if (type == CHILD_PROCESS)//子プロセスは、本家bashと同様にするため、デフォルトのhandlerを設定する
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
}
