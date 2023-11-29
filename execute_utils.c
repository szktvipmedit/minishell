#include "minishell.h"

bool	ft_is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (false);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	// else if (ft_strcmp(cmd, "cd") == 0)
	// 	return (true);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	// else if (ft_strcmp(cmd, "export") == 0)
	// 	return (true);
	// else if (ft_strcmp(cmd, "unset") == 0)
	// 	return (true);
	else if (ft_strcmp(cmd, "env") == 0)
		return (true);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	else
		return (false);
}

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
	ft_exec_path_cmd(node.args, shell->environ_list_head, shell);
}
