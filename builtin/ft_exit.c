#include "../minishell.h"

static int	ft_check_sign(char **str, int *sign, size_t *i)
{
	if ((*str)[*i] == '-' || (*str)[*i] == '+')
	{
			if ((*str)[*i] == '-')
				*sign = -1;
			(*i)++;
	}
	if ((*str)[*i] == '\0')
		return (-1);
	return (0);
}

static int ft_isoverflow(long long nbr, unsigned int digit, int sign)
{
	if (sign == -1)
			return ((LONG_MIN + digit) / 10 > (-1) * nbr);
	else if (sign == 1)
			return ((LONG_MAX - digit) / 10 < nbr);
	return (0);
}

static int	ft_nbr_to_valid_status(long long nbr, int sign)
{
	while (nbr >= 256)
		nbr = nbr % 256;
	if (sign == -1)
	{
		nbr = 256 - nbr;
		if (nbr == 256)//”exit -256”のときのみ例外処理が必要。
			nbr = 0;
	}
	return ((int)nbr);
}

static int	ft_str_to_exit_status(char *str)
{
	size_t		i;
	int				sign;
	long long	nbr;//負の値も格納するため、unsignedは使えない。

	i = 0;
	sign = 1;
	nbr = 0;
	if (ft_check_sign(&str, &sign, &i) == -1)//最初の+-は、次がヌル文字でない限り許容。
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if (ft_isoverflow(nbr, (str[i] - '0'), sign))//long範囲をオーバーフローすると数字のみでもエラー扱いになる。
				return (-1);
			nbr = (10 * nbr) + (str[i] - '0');
			i++;
		}
		else
			return (-1);
	}
	nbr = ft_nbr_to_valid_status(nbr, sign);//終了ステータスとして表示される0~255に変換する。
	return (nbr);
}

void	ft_exit(char **args, t_shell *shell)
{
	if (args[0] == NULL)//exitコマンドに引数がない場合はここでexit。
	{
		ft_put_exit_or_not(shell);
		ft_free_all_and_exit(shell, 0);
	}
	g_exit_status = ft_str_to_exit_status(args[0]);
	if (g_exit_status == -1)//exitコマンドの最初の引数が無効な時点で出るエラー。
	{
		ft_put_exit_or_not(shell);
		ft_printf_stderr("minishell: exit: %s: numeric argument required\n", args[0]);
		ft_free_all_and_exit(shell, WITHOUT_EXIT);
		exit(2);
	}
	if (args[1] != NULL)//exitコマンドの最初の引数は有効かつ、引数が２つ以上ある場合に出るエラー。
	{
		ft_put_exit_or_not(shell);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_exit_status = 1;
		return ;
	}
	ft_put_exit_or_not(shell);//exitコマンドに有効な引数が一つだけの場合。
	ft_free_all_and_exit(shell, WITHOUT_EXIT);
	exit(g_exit_status);
}
