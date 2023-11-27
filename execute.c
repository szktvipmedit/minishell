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
	if (pid == -1)
		ft_free_all_and_exit(shell, 1);
	if (pid == 0)
		ft_exec_child(node[0], shell);
	waitpid(pid, &status, 0);
	ft_set_exit_status(status);
}

void	ft_execute(t_node	*node, t_shell *shell)
{
	ft_set_signal_handler(PARENT_PROCESS);
	if (shell->node_count == 1)
		ft_exec_single_node(node, shell);//パイプが一つもない場合。
	else
		ft_exec_multiple_nodes(node, shell);//パイプがある場合。
}
