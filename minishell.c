#include "minishell.h"

// 端末環境や端末設定の違いによる、ctrlキーの'^C'や'^\'の表示のばらつきを、"表示しない"で統一する
// 表示させたいものを指定したり、再び表示をさせるようにすることもできる
static void	ft_terminal_setting()
{
	struct termios	term_settings;

	tcgetattr(2, &term_settings);//1,端末情報を取得する関数。第一引数には0か1か2を入れる。(これらは端末で関連づけられている)
	term_settings.c_lflag &= ~ECHOCTL;//2,端末情報に変更を加える。
	tcsetattr(1, TCSANOW, &term_settings);//3,設定を反映する関数。TCSANOWは"次回以降の入力から反映する"というオプション
}

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
	if (tmp == NULL)
		ft_msg_and_exit();
	i = 0;
	while (environ[i] != NULL)
	{
		tmp[i] = ft_strdup(environ[i]);
		if (tmp[i] == NULL)
		{
			ft_free_strs(tmp);
			ft_msg_and_exit();
		}
		i++;
	}
	tmp[i] = NULL;
	shell->environ_list_head = tmp;
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
		exit(1);
	}
	ft_terminal_setting();
	ft_initialize_shell(&shell);
	ft_clone_environ_list(&shell);
	ft_shell_loop(&shell);
	exit(0);
}
