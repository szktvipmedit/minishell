#include "../minishell.h"

char *ft_create_cmd_args(char **args)
{
    int i;
    int len;
	i = 0;
	len = 0;

    char *cmd_args;
 	while(args[i])
	{
		len += ft_strlen(args[i++]) + 1;
		if(args[i])
			len++;
	}
	cmd_args = ft_calloc((len + 1),  1);
	i = 0;
    while(args[i])
    {
		ft_strlcat(cmd_args, args[i], len+1);
        i++;
		if(args[i])
			ft_strlcat(cmd_args, " ", len+1);
   }
    return cmd_args;
}
void	ft_split_all_free(char **array)
{
	int	i;

	i = 0;
	if (array == NULL || *array == NULL)
		return ;
	while (array[i] != NULL)
	{
		i++;
	}
	i--;
	while (0 <= i)
		free(array[i--]);
	free(array);
}

char	*getenv_curr_env(char *var_equal, char **envp)
{
	char	*var_addr;

	while (*envp && ft_strncmp(*envp, var_equal, ft_strlen(var_equal)))
		envp++;
	if(*envp == NULL)
		return NULL;
	var_addr = *envp + ft_strlen(var_equal);
	return (var_addr);
}

int	get_cmd_args_cnt(char **split_cmd_args)
{
	int	argc;

	argc = 0;
	while (*split_cmd_args)
	{
		split_cmd_args++;
		argc++;
	}
	return (argc);
}

void	ft_change_envvar(char *var_equal, char *content, t_shell *shell)
{
	size_t	i;
	char		**env;

	env = shell->environ_list_head;
	i = ft_get_env_index(env, var_equal);
	if (env[i] == NULL)
		return ;
	free(env[i]);
	env[i] = ft_strjoin(var_equal, content);
	if (env[i] == NULL)
	{
		ft_free_strs(shell->environ_list_head);
		ft_msg_and_exit();
	}
}
