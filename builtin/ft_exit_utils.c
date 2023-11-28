#include "../minishell.h"

static bool	is_verify_minus_case_is_llnum(char *arg, int *i)
{
	long long	num;

	num = 0;
	while (arg[*i])
	{
		num = num * 10;
		num += arg[*i] - '0';
		if (LLONG_MIN + num > 0)
			return (false);
		*i = *i + 1;
	}
	return (true);
}

static bool	is_verify_plus_case_is_llnum(char *arg, int *i)
{
	long long	num;

	num = 0;
	while (arg[*i])
	{
		num = num * 10;
		num += arg[*i] - '0';
		if (LLONG_MAX - num < 0)
			return (false);
		*i = *i + 1;
	}
	return (true);
}

static bool	verify_is_llnum(char *arg, bool minus_flag, int *i)
{
	if (minus_flag)
	{
		if (!is_verify_minus_case_is_llnum(arg, i))
			return (false);
		else
			return (true);
	}
	else
	{
		if (!is_verify_plus_case_is_llnum(arg, i))
			return (false);
		else
			return (true);
	}
}

bool	is_llnum(char *arg)
{
	int		i;
	bool	minus_flag;

	i = 0;
	minus_flag = false;
	if (arg[0] == '-' || arg[0] == '+')
	{
		if (arg[0] == '-')
			minus_flag = true;
		arg++;
		i++;
	}
	if (verify_is_llnum(arg, minus_flag, &i))
		return (true);
	else
		return (false);
}

bool	isnum(char *arg)
{
	int i;
	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;
	}
	return (true);
}