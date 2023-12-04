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
	
	new_env = (char **)malloc(sizeof(char *) * (len_prev_envp));
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
		{
			new_env[j] = env[i];
			j++;
			i++;
		}
	}
	new_env[j + 1] = NULL;
	free(shell->environ_list_head);
	shell->environ_list_head = new_env;
}

int	is_valid_arg(char *arg)
{
	size_t i;
	i = 0;
	if (ft_strchr(arg, '!'))
	{
		printf("minishell: unset: `%s': not a valid identifier\n", arg);
		g_exit_status=1;
		return (1);
	}
	if (ft_strchr(arg, '='))
	{
		printf("minishell: unset: `%s': not a valid identifier\n", arg);
		g_exit_status=1;
		return (1);
	}
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			printf("minishell: unset: `%s': not a valid identifier\n", arg);
			g_exit_status=1;
			return (1);
		}
		i++;
	}
	return (0);
}