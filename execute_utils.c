#include "minishell.h"

// bool	ft_is_builtin(char *arg)
// {
// 	if (arg == NULL)
// 		return (false);
// 	else if (ft_strcmp(arg, "echo") == 0)
// 		return (true);
// 	else if (ft_strcmp(arg, "cd") == 0)
// 		return (true);
// 	else if (ft_strcmp(arg, "pwd") == 0)
// 		return (true);
// 	else if (ft_strcmp(arg, "export") == 0)
// 		return (true);
// 	else if (ft_strcmp(arg, "unset") == 0)
// 		return (true);
// 	else if (ft_strcmp(arg, "env") == 0)
// 		return (true);
// 	else if (ft_strcmp(arg, "exit") == 0)
// 		return (true);
// 	else
// 		return (false);
// }

void	ft_set_exit_status(int status)
{
	if (WIFSIGNALED(status) != 0)
	{
		if (status == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 2);
		g_exit_status = 128 + WTERMSIG(status);
	}
	else
		g_exit_status = WEXITSTATUS(status);
}

void	ft_exec_child(t_node node, t_shell *shell)
{
	ft_set_signal_handler(CHILD_PROCESS);
	ft_prepare_redirects(node, shell);
	ft_execute_command(node.args, shell->environ_list_head, shell);
}
