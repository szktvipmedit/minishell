#include "../minishell.h"

static void	arg1_case_print(char search, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (envp[i][0] == search)
			printf("declare -x %s\n", envp[i]);
		i++;
	}
}

static void	arg1_case(char **envp)
{
	char	search;

	search = 'A';
	while (search <= 'Z')
	{
		arg1_case_print(search, envp);
		search++;
	}
	arg1_case_print('_', envp);
	search = 'a';
	while (search <= 'z')
	{
		arg1_case_print(search, envp);
		search++;
	}
}

static void	setting_env_variable(char **split_cmd_args, char **envp)
{
	char	*var_name_equal;
	int		i;

	i = 1;
	while (split_cmd_args[i])
	{
		if (split_cmd_args[i][0] == '#')
			arg1_case(envp);
		var_name_equal = ft_strndup(split_cmd_args[i],
				get_name_equal_len(split_cmd_args[i]));
		if (is_valid_new_variable(split_cmd_args[i]))
		{
			i++;
			free(var_name_equal);
			continue ;
		}
		if (is_exist_variable(var_name_equal, envp))
			env_change_content(var_name_equal, split_cmd_args[i], envp);
		else
			append_env_variable(split_cmd_args[i], envp);
		i++;
	}
}

int	ft_export(char *cmd_args, char **envp)
{
	int argc;
	char **split_cmd_args;
	split_cmd_args = ft_split(cmd_args, ' ');
	argc = get_cmd_args_cnt(split_cmd_args);
	if (argc == 1)
		arg1_case(envp);
	else
		setting_env_variable(split_cmd_args, envp);
	ft_split_all_free(split_cmd_args);
	return (0);
}