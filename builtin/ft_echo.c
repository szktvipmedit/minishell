#include "../minishell.h"

static int	ft_check_option_is_valid(char *str)
{
	str++;//先頭の'-'（ハイフン）分、インクリメントする。
	while (*str != '\0')
	{
		if (*str != 'n')
			return (-1);//"-nnn"はオプションとして扱われるが、"-nnn9"などn以外が入った時点でただの文字列として扱われる。
		str++;
	}
	return (0);
}

void	ft_echo(char **args)
{
	bool	is_option_n;
	is_option_n = false;//最初は”-nオプションなし”に設定。
	while (*args != NULL && ft_strncmp(*args, "-n", 2) == 0)//引数の文字列を”一列”ずつ確認する。//最初の２文字だけをチェック。
	{
		if (ft_check_option_is_valid(*args) == -1)//"-n"から始まる引数の文字列を”一文字”ずつ確認する。
			break ;
		is_option_n = true;//一回でも-nオプションが出てきたら以降ずっとtrue。
		args++;
	}
	while (*args != NULL)//オプションとして扱われる引数以降の引数を出力していく。
	{
		ft_printf("%s", *args);//本家のprintfを使うとおかしくなる->バッファーの問題とdiscordで誰か言ってた。
		if (*(args + 1) != NULL)
			write(1, " ", 1);
		args++;
	}
	if (is_option_n == false)//最後に改行するかしないかの判断をする。-nオプションがあるなら改行はしない。
		write(1, "\n", 1);
}
