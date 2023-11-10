#include "minishell.h"

// シグナルが送られたタイミングによってハンドラー関数を変える必要があるため、
// 引数のtypeの値にタイミングを格納してifで場合分けする。
void	ft_set_signal_handler(int type)
{
	if (type == SHELL_LOOP)
	{
		signal(SIGQUIT, SIG_IGN);//このタイミングでの<ctrl-\>はdoes nothing.と課題PDFにあるので、SIG_IGNする。
		signal(SIGINT, ft_display_new_prompt);
	}
	// if (type == )
	// {
	// 	signal(SIGQUIT, );
	// 	signal(SIGINT, );
	// }
}



// rl系の関数はよくわかってないが、お決まりのパターンがあるっぽい。
// このタイミングでは、本家のbashでexit_statusが1に設定されているらしいので再現。
// 課題PDFの要件に従い、ハンドラー関数内でのみ一つだけvolatile sig_atomic_t型のグローバル変数を使用する。
void	ft_display_new_prompt(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 1;
}
