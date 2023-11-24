#include "minishell.h"

static void	ft_manage_pipe_fd_in(int pipe_fd[2])
{
	if (close(pipe_fd[1]) == -1)
		exit(1);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		exit(1);
	if (close(pipe_fd[0]) == -1)
		exit(1);
}

static void	ft_manage_pipe_fd_out(int pipe_fd[2])
{
	if (close(pipe_fd[0]) == -1)
		exit(1);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		exit(1);
	if (close(pipe_fd[1]) == -1)
		exit(1);
}

void	ft_exec_multiple_child(t_node	*node, size_t node_index, t_shell *shell)
{
	if (node_index > 0)//直前にプロセスが存在するか
		ft_manage_pipe_fd_in(node[node_index - 1].pipe_fd);
		//（直前）のプロセスのpipe_fdをcloseしつつ、受け取り口（標準入力）を直前のプロセスの出力先（pipe_fd[0]）に設定する。
	if (node_index < shell->node_count - 1)//直後にプロセスが存在するか
		ft_manage_pipe_fd_out(node[node_index].pipe_fd);
		//（現在）のプロセスのpipe_fdをcloseしつつ、出力先（標準出力）を（pipe_fd[0]）に設定する。
	// if (ft_is_builtin()) == true)
	// {
	// 	ft_exec_single_builtin();
	// 	exit ;
	// }
	ft_exec_child(node[node_index], shell);
}
