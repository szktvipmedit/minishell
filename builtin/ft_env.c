#include "../minishell.h"

static int	setting_env_variable(char *arg, char **envp)
{
	char	*var_name_equal;

	var_name_equal = ft_strndup(arg, get_name_equal_len(arg));
	if (is_valid_new_variable(arg))
	{
		free(var_name_equal);
		return (1);
	}
	if (is_exist_variable(var_name_equal, envp))
		env_change_content(var_name_equal, arg, envp);
	else
		append_env_variable(arg, envp);
	free(var_name_equal);
	return (0);
}

static void	print_env_variable(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		printf("%s\n", envp[i++]);
}

static bool	is_valid_env_setting(char *arg)
{
	while (*arg)
	{
		if (*arg == '=')
			return (true);
		arg++;
	}
	return (false);
}

int	ft_env(char *cmd_args, char **envp, t_node *node, t_shell *shell)
{
	int argc;
	char **envp_copy;
	char **split_cmd_args;

	split_cmd_args = ft_split(cmd_args, ' ');
	argc = get_cmd_args_cnt(split_cmd_args);
	envp_copy = envp;
	if (argc >= 2)
	{
		int i;
		i = 0;
		while (split_cmd_args[i]) //環境変数設定群
		{
			if (split_cmd_args[i][0] == '#')
				break ;
			if (!is_valid_env_setting(split_cmd_args[i]))
				break ;
			setting_env_variable(split_cmd_args[i], envp_copy);
			i++;
		}
		t_node restrict_node;
		t_shell restrict_shell;
		restrict_node = *node;
		restrict_shell = *shell;
		restrict_node.args_count = 0;
		restrict_node.args = NULL;
		restrict_shell.environ_list_head = envp_copy;
		int cmd_start_idx;
		cmd_start_idx = i;
		while (split_cmd_args[i++]) //コマンド実行群
			restrict_node.args_count++;
		restrict_node.args = malloc(sizeof(char **) * restrict_node.args_count);
		i = 0;
		while (split_cmd_args[cmd_start_idx])
			restrict_node.args[i++] = split_cmd_args[cmd_start_idx++];
		ft_exec_single_node(&restrict_node, &restrict_shell);
	}
	print_env_variable(envp_copy);

	return (0);
}