#include "../minishell.h"

void	already_exist_variable_delete(char *var_equal, char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(*envp, var_equal, ft_strlen(var_equal)))
		envp++;
	while (envp[i] != NULL)
	{
		envp[i] = envp[i + 1];
		i++;
	}
	// printf("getenv_curr_env: %s\n", var_addr);
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