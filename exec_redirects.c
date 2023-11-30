#include "minishell.h"

static void	ft_ambiguous_redirect(char *target_name, t_shell *shell)
{
	ft_printf_stderr("minishell: %s: ambiguous redirect\n", target_name + 2);//$?以降の元々のtarget_name
	if (shell->is_single_node_builtin == 1)
	{
		shell->single_node_builtin_error = -1;
		g_exit_status = 1;
		return ;
	}
	ft_free_all_and_exit(shell, WITHOUT_EXIT);
	exit(1);
}

static int	ft_open_error_and_exit(char *file_name, t_shell *shell)
{
	if (errno == ENOENT)
		ft_printf_stderr("minishell: %s: No such file or directory\n", file_name);
	if (shell->is_single_node_builtin == 1)//このケースだけは親プロセスのためexitできない。例外処理が必要。
	{
		shell->single_node_builtin_error = -1;
		g_exit_status = 1;//builtinの終了ステータスを1にセットする。
		return (-1);//とりあえずexitせずにこの関数を終わらせたい。
	}
	ft_free_all_and_exit(shell, WITHOUT_EXIT);
	exit(1);
}

static int	ft_get_infile(t_node	node, t_redirect redirect, t_shell *shell)
{
	int	fd;

	fd = 0;
	if (redirect.type == INPUTFILE)
		fd = open(redirect.target_name, O_RDONLY);
	if (fd == -1)
		return (ft_open_error_and_exit(redirect.target_name, shell));
	if (redirect.type == DELIMITER)
		fd = open(node.temp_file, O_RDONLY);
	if (fd == -1)
		return (ft_open_error_and_exit(node.temp_file, shell));
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_free_all_and_exit(shell, 1);
	if (close(fd) == -1)
		ft_free_all_and_exit(shell, 1);
	return (0);
}

static int	ft_get_outfile(t_redirect redirect, t_shell *shell)
{
	int	fd;

	fd = 0;
	if (redirect.type == OUTPUTFILE)
		fd = open(redirect.target_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirect.type == APPENDFILE)
		fd = open(redirect.target_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (ft_open_error_and_exit(redirect.target_name, shell));
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_free_all_and_exit(shell, 1);
	if (close(fd) == -1)
		ft_free_all_and_exit(shell, 1);
	return (0);
}

void	ft_prepare_redirects(t_node	node, t_shell *shell)
{
	size_t	i;

	if (node.redirects_count == 0)
		return ;
	i = 0;
	while (i < node.redirects_count)
	{
		if (node.redirects[i].type == INPUTFILE || node.redirects[i].type == DELIMITER)
		{
			if (ft_is_amb(node.redirects[i].type, node.redirects[i].target_name))//delimiterは例外
				return (ft_ambiguous_redirect(node.redirects[i].target_name, shell));
			if (ft_get_infile(node, node.redirects[i], shell) == -1)
				return ;
		}
		if (node.redirects[i].type == OUTPUTFILE || node.redirects[i].type == APPENDFILE)
		{
			if (ft_strncmp(node.redirects[i].target_name, "$?", 2) == 0)//$?がexpandされずに残ってる＝異常事態
				return (ft_ambiguous_redirect(node.redirects[i].target_name, shell));
			if (ft_get_outfile(node.redirects[i], shell) == -1)
				return ;
		}
		i++;
	}
}
