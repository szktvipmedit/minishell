#include "../minishell.h"

static void	setting_env_variable(char **split_cmd_args, char **envp, t_shell *shell)
{
	char	*var_name_equal;
	int		i;

	i = 1;
	while (split_cmd_args[i])
	{
		if (split_cmd_args[i][0] == '#')
			return ;
		var_name_equal = ft_strndup(split_cmd_args[i],
				get_name_equal_len(split_cmd_args[i]));
		if(!var_name_equal) 
			ft_free_all_and_exit(shell, 1);
		if (is_valid_arg(split_cmd_args[i]))
		{
			i++;
			free(var_name_equal);
			continue ;
		}
		if (is_exist_variable(var_name_equal, envp))
			already_exist_variable_delete(var_name_equal, envp);
		i++;
	}
}

int	ft_unset(char *cmd_args, t_shell *shell)
{
	int argc;
	char **split_cmd_args;
	split_cmd_args = ft_split(cmd_args, ' ');
    if(!split_cmd_args) 
        ft_free_all_and_exit(shell, 1);
	argc = get_cmd_args_cnt(split_cmd_args);
	if (argc == 1)
		return (0);
	else
		setting_env_variable(split_cmd_args, shell->environ_list_head, shell);
	ft_split_all_free(split_cmd_args);
	return (0);
}