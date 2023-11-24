#include "minishell.h"

static int	ft_check_last_infile_type(t_redirect *redirects, size_t redirect_count)
{
	size_t	i;
	int			result;

	i = 0;
	result = 0;
	while (i < redirect_count)
	{
		if (redirects[i].type == DELIMITER)
			result = 1;
		if (redirects[i].type == INPUTFILE)
			result = 2;
		i++;
	}
	return (result);
}

static size_t	ft_get_last_inputfile_index(t_redirect *redirects, size_t redirect_count)
{
	size_t	i;
	size_t	result;

	i = 0;
	result = 0;
	while (i < redirect_count)
	{
		if (redirects[i].type == INPUTFILE)
			result = i;
		i++;
	}
	return (result);
}

static void	ft_get_infile(t_node	node, t_redirect *redirects, size_t redirect_count, t_shell *shell)
{
	int	fd;

	(void)shell;
	if (ft_check_last_infile_type(redirects, redirect_count) == 0)
		return ;
	else if (ft_check_last_infile_type(redirects, redirect_count) == 1)
		fd = open(node.temp_file, O_RDONLY);
	else
		fd = open(redirects[ft_get_last_inputfile_index(redirects, redirect_count)].target_name, O_RDONLY);
	// if (fd == -1)
	// 	error
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	ft_get_outfile(t_redirect *redirects, size_t redirect_count, t_shell *shell)
{
	size_t	i;
	int			fd;

	(void)shell;
	i = 0;
	fd = 0;
	while (i < redirect_count)
	{
		if (redirects[i].type == OUTPUTFILE)
			fd = open(redirects[i].target_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redirects[i].type == APPENDFILE)
			fd = open(redirects[i].target_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// if (fd == -1)
		// 	error
		if (fd != 0)
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
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
