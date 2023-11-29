#include "minishell.h"

void	ft_free_all_and_exit(t_shell *shell, int	exit_type)
{
	ft_delete_heredoc_file(shell->node_head, shell);
	ft_free_strs(shell->environ_list_head);
	if (shell->line != NULL)
		free(shell->line);
	ft_free_token(shell->token_head);
	ft_free_node(shell->node_head, shell);
	if (exit_type == WITHOUT_EXIT)
		return ;
	if (exit_type == 1)
		ft_msg_and_exit();
	exit(0);
}

void	ft_msg_and_exit()
{
	ft_putstr_fd("Fatal error. exit\n", 2);
	exit(1);
}

void	ft_delete_heredoc_file(t_node *node, t_shell *shell)
{
	size_t	i;

	if (node == NULL)
		return ;
	i = 0;
	while (i < shell->node_count)
	{
		if (access(node[i].temp_file, R_OK) == 0)
		{
			if (unlink(node[i].temp_file) == -1)
				ft_free_all_and_exit(shell, 1);
		}
		i++;
	}
}
