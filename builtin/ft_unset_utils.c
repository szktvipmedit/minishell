#include "../minishell.h"

void	already_exist_variable_delete(char *var_equal, char **env, t_shell *shell)
{
	size_t	i;
	size_t  j;
	size_t 	len_prev_envp;
	char **new_env;
	i = 0;
	j = 0;
	len_prev_envp = 0;
	while(env[len_prev_envp] != NULL)
		len_prev_envp++;
	new_env = (char **)malloc(sizeof(char *) * (len_prev_envp - 1));
    if(!new_env) 
        ft_free_all_and_exit(shell, 1);
	while (env[i] != NULL)
	{
		if(!ft_strncmp(env[i], var_equal, ft_strlen(var_equal)))
		{
			free(env[i]);
			i++;
		}
		else
			new_env[j++] = env[i++];
	}
	new_env[i + 1] = NULL;
	free(shell->environ_list_head);
	shell->environ_list_head = new_env;
}

int	is_valid_arg(char *arg)
{
	char *init_arg;
	init_arg = arg;
	if (ft_strchr(init_arg, '='))
	{
		printf("minishell: unset: `%s': not a valid identifier\n", init_arg);
		return (1);
	}
	while (*arg)
	{
		if (!ft_isalnum(*arg) && *arg != '_' && *arg != '=' && *(arg
				+ 1) != '\0')
		{
			if (*arg == '!')
			{
				if (*(arg + 1) == '=')
					printf("minishell: export: `%s': not a valid identifier\n",
						init_arg);
				else
					printf("minishell: %s: event not found\n", arg);
			}
			else
				printf("minishell: export: `%s': not a valid identifier\n",
					init_arg);
			return (1);
		}
		arg++;
	}
	return (0);
}