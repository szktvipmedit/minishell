#include "../minishell.h"

bool	is_exist_variable(char *var_equal, char **env)
{
	size_t	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], var_equal, ft_strlen(var_equal)) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	get_name_equal_len(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			break ;
		i++;
	}
	i++;
	return (i);
}

static int	is_include_exc(char *arg)
{
	size_t	i;

	while (arg[i])
	{
		if (arg[i] == '!')
		{
			ft_putstr_fd("Sorry, minishell does not support `!'.\n", 2);
			g_exit_status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	count_var_name_char(char *arg, size_t *var_len)
{
	while (arg[*var_len])
	{
		if (arg[*var_len] == '=')
			break ;
		*var_len = *var_len + 1;
	}
	if (*var_len == 0)
	{
		ft_printf_stderr("minishell: export: `%s': not a valid identifier\n",
			arg);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

int	is_valid_new_variable(char *arg)
{
	size_t i;
	size_t var_len;
	var_len = 0;
	i = 0;
	if (is_include_exc(arg))
		return (1);
	if (count_var_name_char(arg, &var_len))
		return (1);
	while (i < var_len && arg[i])
	{
		if (!ft_isalpha(arg[i]) && arg[i] != '_')
		{
			ft_printf_stderr("minishell: export: `%s': not a valid identifier\n",
				arg);
			g_exit_status = 1;
			return (1);
		}
		i++;
	}
	if (var_len == ft_strlen(arg))
		return (1);
	return (0);
}