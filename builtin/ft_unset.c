#include "../minishell.h"

static int	is_incs_error_char(char *arg)
{
	if (ft_strchr(arg, '!'))
	{
		ft_printf_stderr("minishell: unset: `%s': not a valid identifier\n",
			arg);
		g_exit_status = 1;
		return (1);
	}
	if (ft_strchr(arg, '='))
	{
		ft_printf_stderr("minishell: unset: `%s': not a valid identifier\n",
			arg);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

static int	is_valid_arg(char *arg)
{
	size_t	i;

	i = 0;
	if (is_incs_error_char(arg))
		return (1);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			ft_printf_stderr("minishell: unset: `%s': not a valid identifier\n",
				arg);
			g_exit_status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

static void	setting_env_variable(char **args, t_shell *shell)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '#')
			return ;
		if (is_valid_arg(args[i]))
		{
			i++;
			continue ;
		}
		if (is_exist_variable(args[i], shell->environ_list_head))
			already_exist_variable_delete(args[i], shell->environ_list_head,
				shell);
		i++;
	}
}

int	ft_unset(char **args, t_shell *shell)
{
	int argc;
	char *cmd_args;
	cmd_args = ft_create_cmd_args(args);
	argc = get_cmd_args_cnt(args);

	if (argc == 0)
		;
	else
		setting_env_variable(args, shell);
	free(cmd_args);
	return (0);
}