#include "minishell.h"

static void	ft_wait_child_Processes(t_node *node, t_shell *shell)
{
	size_t	i;
	int			status;

	i = 0;
	while (i < shell->node_count)
	{
		if (waitpid(node[i].pid, &status, 0) == -1)
			ft_free_all_and_exit(shell, 1);
		i++;
	}
	ft_set_exit_status(status);
}
 
static void	ft_close_used_pipe(t_node *node, size_t i, t_shell *shell)
{
	if (i == 0)
		return ;

	if (close(node[i - 1].pipe_fd[0]) == -1)
		ft_free_all_and_exit(shell, 1);
	if (close(node[i - 1].pipe_fd[1]) == -1)
		ft_free_all_and_exit(shell, 1);
}

void	ft_exec_multiple_nodes(t_node	*node, t_shell *shell)
{
	size_t	i;

	i = 0;
	while (i < shell->node_count)
	{
		if (i < shell->node_count - 1)
		{
			if (pipe(node[i].pipe_fd) == -1)
				ft_free_all_and_exit(shell, 1);
		}
		node[i].pid = fork();
		if (node[i].pid == -1)
			ft_free_all_and_exit(shell, 1);
		if (node[i].pid == 0)
			ft_exec_multiple_child(node, i, shell);
		else
			ft_close_used_pipe(node, i, shell);
		i++;
	}
	ft_wait_child_Processes(node, shell);
}
