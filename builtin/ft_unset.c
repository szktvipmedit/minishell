#include "../minishell.h"

static void	setting_env_variable(char **args, t_shell *shell)
{
	int		i;

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
		printf("args %s\n", args[i]);
		if (is_exist_variable(args[i], shell->environ_list_head))
			already_exist_variable_delete(args[i], shell->environ_list_head,  shell);
		i++;
	}
}

int	ft_unset(char **args, t_shell *shell)
{
	int argc;
	char *cmd_args;
	cmd_args = ft_create_cmd_args(args);
	argc = get_cmd_args_cnt(args);
	
	if (argc == 0);
	else
		setting_env_variable(args,  shell);
	free(cmd_args);
	return (0);
}