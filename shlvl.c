#include "minishell.h"
size_t	ft_get_env_index(char **env, char *str)
{
	size_t	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
			return (i);
		i++;
	}
	return (i);
}

void	ft_increment_shlvl(t_shell *shell)
{
	size_t	i;
	int			prev_lvl;
	char		*tmp;
	char *new_lvl;

	i = ft_get_env_index(shell->environ_list_head, "SHLVL=");
	if (shell->environ_list_head[i] == NULL)
		return ;
	prev_lvl = ft_atoi(shell->environ_list_head[i] + 6);
	tmp = shell->environ_list_head[i];
	new_lvl = ft_itoa(prev_lvl + 1);
	if(!new_lvl)
	{
		ft_free_strs(shell->environ_list_head);
		ft_msg_and_exit();
	}
	shell->environ_list_head[i] = ft_strjoin("SHLVL=", new_lvl);
	if (shell->environ_list_head[i] == NULL)
	{
		ft_free_strs(shell->environ_list_head);
		ft_msg_and_exit();
	}
	free(new_lvl);
	free(tmp);
}
