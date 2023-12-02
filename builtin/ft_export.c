#include "../minishell.h"

static void	arg1_case_print(char search, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		int j = 0;
		if(search == '_' && envp[i][1] == '=')
			return ;
		if (envp[i][j] == search)
		{
        	printf("declare -x ");
			while(envp[i][j] && envp[i][j] != '=')
				printf("%c", envp[i][j++]);
			if(envp[i][j] && envp[i][j++] == '=')
				printf("=");
			printf("\"");
			while(envp[i][j] && envp[i][j] != '=')
				printf("%c", envp[i][j++]);
			printf("\"\n");
		}
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

static void	setting_env_variable(char **split_cmd_args, char **envp, t_shell *shell)
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
    	if(!var_name_equal) 
   		    ft_free_all_and_exit(shell, 1);
		if (is_valid_new_variable(split_cmd_args[i]))
		{
			i++;
			free(var_name_equal);
			continue ;
		}
		if (is_exist_variable(var_name_equal, envp))
			env_change_content(var_name_equal, split_cmd_args[i], envp);
		else
			append_env_variable(split_cmd_args[i], envp, shell);
		i++;
	}
}

int	ft_export(char *cmd_args, t_shell *shell)
{
	int argc;
	char **split_cmd_args;
	split_cmd_args = ft_split(cmd_args, ' ');
    if(!split_cmd_args) 
        ft_free_all_and_exit(shell, 1);
	argc = get_cmd_args_cnt(split_cmd_args);
	if (argc == 1)
		arg1_case(shell->environ_list_head);
	else
		setting_env_variable(split_cmd_args, shell->environ_list_head, shell);
	ft_split_all_free(split_cmd_args);
	return (0);
}