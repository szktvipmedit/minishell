#include "../minishell.h"

static long long	ato_ll(char *arg)
{
	long long	num;
	int			i;
	bool		minus_flag;

	//確実にlonglongに収まる状況で入る(signed intに収まるかはまだわからない状況
	minus_flag = false;
	num = 0;
	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
	{
		if (arg[0] == '-')
			minus_flag = true;
		i++;
	}
	while (arg[i])
	{
		num = num * 10;
		num += arg[i] - '0';
		i++;
	}
	if (minus_flag)
		num = num * -1;
	return (num);
}

static int	ft_exit_exist_arg(int argc, signed int *arg_value,
		char **split_cmd_args)
{
	if (!isnum(split_cmd_args[1]) || !is_llnum(split_cmd_args[1])) //引数が大きすぎ
	{
		printf("minishell: exit: %s: numeric argument required\n",
			split_cmd_args[1]);
		*arg_value = 255;
	}
	else //第二引数(exitの次)がまとも
	{
		*arg_value = ato_ll(split_cmd_args[1]);
		if (*arg_value >= 256)
			*arg_value = *arg_value % 256;
		if (argc > 2)
		{
			printf("minishell: exit: too many arguments\n");
			return (1);
		}
	}
	return (0);
}

//引数にエラーがあっても基本は終了する(第一引数が数字の時のみ終了しない)
int	ft_exit(char *cmd_args)
{
	int			argc;
	char		**split_cmd_args;
	signed int	arg_value;

	arg_value = 0;
	split_cmd_args = ft_split(cmd_args, ' ');
	argc = get_cmd_args_cnt(split_cmd_args);
	printf("exit\n");
	if (argc == 1)
		arg_value = 0;
	else
	{
		if (ft_exit_exist_arg(argc, &arg_value, split_cmd_args))
			return (1);
	}
	ft_split_all_free(split_cmd_args);
	exit(arg_value);
	return (0);
}

// int main()
// {
// ft_exit("exit +9223372036854775808");//bash: exit:
// +9223372036854775808: numeric argument required , $? = 255
// ft_exit("exit -9223372036854775809");//bash: exit:
// -9223372036854775809: numeric argument required
// ft_exit("exit -9223372036854775808");
// ft_exit("exit -9223372036854775807");//$?=1
// ft_exit("exit +9223372036854775807");
// ft_exit("exit -123456789123456789123456789123456789123456789");//bash: exit:
// -123456789123456789123456789123456789123456789: numeric argument required
// ft_exit("exit -5");//echo $? == 251
// ft_exit("exit a");//bash: exit: a: numeric argument required
// ft_exit("exit 9223372036854775808");//bash: exit: 9223372036854775808: numeric argument required
// ft_exit("exit 9223372036854775807"); //$? = 255
// ft_exit("exit a 134 13");//bash: exit: a: numeric argument required
// ft_exit("exit 6 1 3");//bash: exit: too many arguments
// ft_exit("exit 6 qewfio a");//bash: exit: too many arguments
// ft_exit("exit 6");// $? = 6

//     return (0);
// }