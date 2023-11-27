#include "minishell.h"

static void	ft_open_error_and_exit(char *file_name, t_shell *shell)
{
	if (errno == ENOENT)
		ft_printf_stderr("minishell: %s: No such file or directory\n", file_name);
	ft_free_all_and_exit(shell, WITHOUT_EXIT);
	exit(1);
}

static void	ft_get_infile(t_node	node, t_redirect *redirects, size_t redirect_count, t_shell *shell)
{
	size_t	i;
	int			fd;

	i = 0;
	fd = 0;
	while (i < redirect_count)
	{
		if (redirects[i].type == INPUTFILE)
			fd = open(redirects[i].target_name, O_RDONLY);
		if (fd == -1)
			ft_open_error_and_exit(redirects[i].target_name, shell);
		if (redirects[i].type == DELIMITER)
			fd = open(node.temp_file, O_RDONLY);
		if (fd == -1)
			ft_open_error_and_exit(node.temp_file, shell);
		if (fd != 0)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
				ft_free_all_and_exit(shell, 1);
			if (close(fd) == -1)
				ft_free_all_and_exit(shell, 1);
			fd = 0;
		}
		i++;
	}
}

static void	ft_get_outfile(t_redirect *redirects, size_t redirect_count, t_shell *shell)
{
	size_t	i;
	int			fd;

	i = 0;
	fd = 0;
	while (i < redirect_count)
	{
		if (redirects[i].type == OUTPUTFILE)
			fd = open(redirects[i].target_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redirects[i].type == APPENDFILE)
			fd = open(redirects[i].target_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			ft_open_error_and_exit(redirects[i].target_name, shell);
		if (fd != 0)
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
				ft_free_all_and_exit(shell, 1);
			if (close(fd) == -1)
				ft_free_all_and_exit(shell, 1);
			fd = 0;
		}
		i++;
	}
}

void	ft_prepare_redirects(t_node	node, t_shell *shell)
{
	if (node.redirects_count == 0)
		return ;
	ft_get_infile(node, node.redirects, node.redirects_count, shell);
	ft_get_outfile(node.redirects, node.redirects_count, shell);
}
