#include "minishell.h"

void	ft_free_all_and_exit(t_shell *shell)
{
	ft_free_strs(shell->environ_list_head);
	free(shell->line);
	ft_free_token(shell->token_head);
	ft_free_node(shell->node_head, shell);
	ft_msg_and_exit();
}

void	ft_msg_and_exit()
{
	ft_putstr_fd("Fatal error. exit\n", 2);
	exit(1);
}
