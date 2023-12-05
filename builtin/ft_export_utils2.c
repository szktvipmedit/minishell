#include "../minishell.h"

void	append_env_variable(char *text, char **env, t_shell *shell)
{
	size_t	i;
	size_t	len_prev_envp;
	char	**new_env;

	i = 0;
	len_prev_envp = 0;
	while (env[len_prev_envp] != NULL)
		len_prev_envp++;
	new_env = (char **)malloc(sizeof(char *) * (len_prev_envp + 1));
	if (!new_env)
		ft_free_all_and_exit(shell, 1);
	while (env[i] != NULL)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = ft_strdup(text);
	if (!new_env[i])
		ft_free_all_and_exit(shell, 1);
	new_env[i + 1] = NULL;
	free(shell->environ_list_head);
	shell->environ_list_head = new_env;
}

void	env_change_content(char *var_equal, char *text, t_shell *shell)
{
	char *new_variable;
	char **envp;

	envp = shell->environ_list_head;
	while (ft_strncmp(*envp, var_equal, ft_strlen(var_equal)))
		envp++;
	new_variable = ft_strdup(text);
	if (!new_variable)
		ft_free_all_and_exit(shell, 1);
	ft_strlcat(new_variable, text, ft_strlen(text));
	free(*envp);
	*envp = new_variable;
	// printf("getenv_curr_env: %s\n", var_addr);
}