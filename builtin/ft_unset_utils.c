#include "../minishell.h"

static void	store_variable(char **env, char **new_env, size_t *i, size_t *j)
{
	new_env[*j] = env[*i];
	*j = *j + 1;
	*i = *i + 1;
}

static size_t	get_env_len(char **env)
{
	size_t	len_prev_envp;

	len_prev_envp = 0;
	while (env[len_prev_envp] != NULL)
		len_prev_envp++;
	return (len_prev_envp);
}

void	already_exist_variable_delete(char *var_equal, char **env,
		t_shell *shell)
{
	size_t	i;
	size_t	j;
	size_t	len_prev_envp;
	char	**new_env;

	i = 0;
	j = 0;
	len_prev_envp = get_env_len(env);
	new_env = (char **)malloc(sizeof(char *) * (len_prev_envp));
	if (!new_env)
		ft_free_all_and_exit(shell, 1);
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], var_equal, ft_strlen(var_equal)))
		{
			free(env[i]);
			i++;
		}
		else
			store_variable(env, new_env, &i, &j);
	}
	new_env[j + 1] = NULL;
	free(shell->environ_list_head);
	shell->environ_list_head = new_env;
}
