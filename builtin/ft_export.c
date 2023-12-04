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

static void	setting_env_variable(char **args, char **envp, t_shell *shell)
{
	char	*var_name_equal;
	int		i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '#')
			arg1_case(envp);
		var_name_equal = ft_strndup(args[i],
				get_name_equal_len(args[i]));
    	if(!var_name_equal) 
   		    ft_free_all_and_exit(shell, 1);
		if (is_valid_new_variable(args[i]))
		{
			i++;
			free(var_name_equal);
			continue ;
		}
		if (is_exist_variable(var_name_equal, envp))
			env_change_content(var_name_equal, args[i], shell);
		else 
			append_env_variable(args[i], envp, shell);
		i++;
		free(var_name_equal);
	}
}

void 	ft_export(char **args, t_shell *shell)
{
	int argc;
	char *cmd_args;
	cmd_args = ft_create_cmd_args(args);
	argc = get_cmd_args_cnt(args);
	if (argc == 0)
		arg1_case(shell->environ_list_head);
	else
		setting_env_variable(args, shell->environ_list_head, shell);
	free(cmd_args);
	return ;
}