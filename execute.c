#include "minishell.h"

static void	ft_exec_single_node(t_node	*node, t_shell *shell)
{
	pid_t	pid;
	int		status;
	
	// if (ft_is_builtin(node[0].args[0]) == true)
	// {
	// 	ft_exec_single_builtin();
	// 	return ;
	// }
	pid = fork();
	// if (pid == -1)
	// 	ft_error("fork");
	if (pid == 0)
		ft_exec_child(node[0], shell);
	waitpid(pid, &status, 0);
	// g_exit_status = WEXITSTATUS(status);
}

void	ft_execute(t_node	*node, t_shell *shell)
{
	if (shell->node_count == 1)
		ft_exec_single_node(node, shell);
	else
		ft_exec_multiple_nodes(node, shell);
}
