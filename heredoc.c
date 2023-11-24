#include "minishell.h"

static char	*ft_create_temp_file(size_t node_index, t_shell *shell)
{
	char	*temp_file;
	char	*index_number;

	index_number = ft_itoa(node_index);
	if (index_number == NULL)
		ft_free_all_and_exit(shell);
	temp_file = ft_strjoin(".temp_heredoc", index_number);
	if (temp_file == NULL)
		ft_free_all_and_exit(shell);
	free(index_number);
	return (temp_file);
}

static void	ft_get_infile_heredoc(t_node *node, char *delimiter, t_shell *shell)
{
	int		temp_fd;
	char	*buf;

	(void)shell;
	temp_fd = open(node->temp_file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(temp_fd < 0)
		ft_free_all_and_exit(shell);
	while(1)
	{
		write(2, "> ", 2);
		buf = get_next_line(0);
		if(!buf)
			ft_free_all_and_exit(shell);
		if(!ft_strncmp(delimiter, buf, ft_strlen(delimiter)) && ((ft_strlen(buf) - 1) == ft_strlen(delimiter)))//改行分の-1
		{
			free(buf);
			break;
		}
		//実装するならここでexpandできるかできないか->できるならする。
		write(temp_fd, buf, ft_strlen(buf));
		free(buf);
	}
	close(temp_fd);
}

static void	ft_search_heredoc(t_redirect	*redirects, t_node *node, size_t node_index, t_shell *shell)
{
	size_t	i;

	i = 0;
	while (i < node->redirects_count)
	{
		if (redirects[i].type == DELIMITER)
		{
			if (node->temp_file == NULL)
				node->temp_file = ft_create_temp_file(node_index, shell);
			ft_get_infile_heredoc(node, redirects[i].target_name, shell);
		}
		i++;
	}
}

void	ft_heredoc(t_node *node, t_shell *shell)
{
	size_t	i;

	i = 0;
	while (i < shell->node_count)
	{
		ft_search_heredoc(node[i].redirects, &node[i], i, shell);
		i++;
	}
}
