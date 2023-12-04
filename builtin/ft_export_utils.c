#include "../minishell.h"

void	append_env_variable(char *text, char **env, t_shell *shell)
{
	size_t	i;
	size_t 	len_prev_envp;
	char **new_env;
	i = 0;
	len_prev_envp = 0;
	while(env[len_prev_envp] != NULL)
		len_prev_envp++;	
	new_env = (char **)malloc(sizeof(char *) * (len_prev_envp + 1));
    if(!new_env) 
        ft_free_all_and_exit(shell, 1);
	while (env[i] != NULL)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = ft_strdup(text);
    if(!new_env[i]) 
        ft_free_all_and_exit(shell, 1);
	new_env[i + 1] = NULL;
	free(shell->environ_list_head);
	shell->environ_list_head = new_env;
}

void	env_change_content(char *var_equal, char *text,  t_shell *shell)
{
	char *new_variable;
	char **envp;
	envp = shell->environ_list_head;
	while (ft_strncmp(*envp, var_equal, ft_strlen(var_equal)))
		envp++;
	new_variable = ft_strdup(text);
	if(!new_variable)
		ft_free_all_and_exit(shell, 1);
	ft_strlcat(new_variable, text, ft_strlen(text));
	free(*envp);
	*envp = new_variable;
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
	size_t i=0;
	size_t var_len;
	var_len = 0;
	//!をまず弾く
	while(arg[i])
	{
		if(arg[i] == '!')
		{
			ft_putstr_fd("Sorry, minishell does not support `!'.\n", 2);
			g_exit_status = 1;
			return 1;
		}
		i++;
	}	
	i=0;
	while(arg[var_len])
	{
		if(arg[var_len] == '=')
			break;
		var_len++;
	}
	if(var_len == 0)
	{
		ft_printf_stderr("minishell: export: `%s': not a valid identifier\n",arg);
		g_exit_status = 1;
		return 1;
	}
	while(i < var_len && arg[i])
	{
		if(!ft_isalpha(arg[i]) && arg[i] != '_')
		{
			ft_printf_stderr("minishell: export: `%s': not a valid identifier\n",arg);
			g_exit_status = 1;
			return 1;
		}
		i++;
	}
	if(var_len == ft_strlen(arg))
		return 1;
	return (0);
}