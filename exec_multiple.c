#include "minishell.h"

static void	ft_wait_child_Processes(t_node *node, t_shell *shell)
{
	size_t	i;
	int			status;

	i = 0;
	while (i < shell->node_count)
	{
		if (waitpid(node[i].pid, &status, 0) == -1)
			exit(1);
		i++;
	}
	g_exit_status = WEXITSTATUS(status);
}
 
static void	ft_close_used_pipe(t_node *node, size_t i)
{
	if (i == 0)// もう使わなくなったpipe_fdがまだない
		return ;

	if (close(node[i - 1].pipe_fd[0]) == -1)
		exit(1);
	if (close(node[i - 1].pipe_fd[1]) == -1)// もう使わなくなった一つ手前のnodeのpipe_fdをcloseする
		exit(1);
}

void	ft_exec_multiple_nodes(t_node	*node, t_shell *shell)
{
	size_t	i;

	i = 0;
	while (i < shell->node_count)
	{
		if (i < shell->node_count - 1)//最後のnode分はパイプする必要ないため
		{
			if (pipe(node[i].pipe_fd) == -1)
				exit(1);
		}
		node[i].pid = fork();
		if (node[i].pid == -1)
			exit(1);
		if (node[i].pid == 0)
			ft_exec_multiple_child(node, i, shell);
		else
			ft_close_used_pipe(node, i);
		i++;
	}
	ft_wait_child_Processes(node, shell);
}
