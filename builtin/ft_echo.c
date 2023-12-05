#include "../minishell.h"

static int	ft_check_option_is_valid(char *str)
{
	str++;
	while (*str != '\0')
	{
		if (*str != 'n')
			return (-1);
		str++;
	}
	return (0);
}

void	ft_echo(char **args)
{
	bool	is_option_n;

	is_option_n = false;
	while (*args != NULL && ft_strncmp(*args, "-n", 2) == 0)
	{
		if (ft_check_option_is_valid(*args) == -1)
			break ;
		is_option_n = true;
		args++;
	}
	while (*args != NULL)
	{
		ft_printf("%s", *args);
		if (*(args + 1) != NULL)
			write(1, " ", 1);
		args++;
	}
	if (is_option_n == false)
		write(1, "\n", 1);
}
