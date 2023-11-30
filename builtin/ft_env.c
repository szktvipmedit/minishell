#include "../minishell.h"

void	ft_env(char **args, t_shell *shell)
{
	size_t	i;

	if (args[0] != NULL)//envコマンドに引数があればエラーとみなす。
	{
		ft_putstr_fd("Sorry, minishell only support env with no options or arguments.\n", 2);
		g_exit_status = 127;//なるべく本家によせるため。
		return ;
	}
	i = 0;
	while (shell->environ_list_head[i] != NULL)
	{
		printf("%s\n", shell->environ_list_head[i]);
		i++;
	}
}
