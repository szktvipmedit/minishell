#include "minishell.h"

static void	ft_manage_pipe_fd_in(int pipe_fd[2], t_shell *shell)
{
	if (close(pipe_fd[1]) == -1)
		ft_free_all_and_exit(shell, 1);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		ft_free_all_and_exit(shell, 1);
	if (close(pipe_fd[0]) == -1)
		ft_free_all_and_exit(shell, 1);
}

static void	ft_manage_pipe_fd_out(int pipe_fd[2], t_shell *shell)
{
	if (close(pipe_fd[0]) == -1)
		ft_free_all_and_exit(shell, 1);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		ft_free_all_and_exit(shell, 1);
	if (close(pipe_fd[1]) == -1)
		ft_free_all_and_exit(shell, 1);
}

void	ft_exec_multiple_child(t_node *node, size_t node_index, t_shell *shell)
{
	if (node_index > 0)
		ft_manage_pipe_fd_in(node[node_index - 1].pipe_fd, shell);
	if (node_index < shell->node_count - 1)
		ft_manage_pipe_fd_out(node[node_index].pipe_fd, shell);
	if (ft_is_builtin(node[node_index].args[0]) == true)
	{
		ft_exec_builtin(node[node_index], shell);
		ft_free_all_and_exit(shell, WITHOUT_EXIT);
		exit(g_exit_status);//ft_exec_builtin内ではexitしないため、ここでexitする。終了ステータスはbuiltin関数内で更新済み。
	}
	ft_exec_child(node[node_index], shell);
}
