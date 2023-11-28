#include "../minishell.h"

void	append_env_variable(char *text, char **env)
{
	size_t	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	env[i] = ft_strdup(text);
	env[i + 1] = NULL;
}

void	env_change_content(char *var_equal, char *text, char **envp)
{
	while (ft_strncmp(*envp, var_equal, ft_strlen(var_equal)))
		envp++;
	*envp = ft_strdup(text);
	// printf("getenv_curr_env: %s\n", var_addr);
}

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

int	is_valid_new_variable(char *arg)
{
	char *init_arg;
	init_arg = arg;
	if (!ft_strchr(init_arg, '='))
		return (1);
	while (*arg)
	{
		if (!ft_isalnum(*arg) && *arg != '_' && *arg != '=' && *(arg
				+ 1) != '\0')
		{
			if (*arg == '!')
			{
				if (*(arg + 1) == '=')
					printf("-minishell: export: `%s': not a valid identifier\n",
						init_arg);
				else
					printf("-minishell: %s: event not found\n", arg);
			}
			else
				printf("-minishell: export: `%s': not a valid identifier\n",
					init_arg);
			return (1);
		}
		arg++;
	}
	return (0);
}