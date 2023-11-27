#include "minishell.h"

void	ft_free_all_and_exit(t_shell *shell, int	exit_type)
{
	ft_delete_heredoc_file(shell->node_head, shell);//nodeの情報を使用するため、nodeをfreeするまえに実行。
	ft_free_strs(shell->environ_list_head);
	if (shell->line != NULL)
		free(shell->line);
	ft_free_token(shell->token_head);
	ft_free_node(shell->node_head, shell);
	if (exit_type == -1)//全てfreeしたいけど、exitする際の終了ステータスやメッセージをカスタマイズしたい場合。
		return ;
	if (exit_type == 1)//主にmallocやcloseなどの関数が失敗した場合。
		ft_msg_and_exit();
	exit(0);
}

void	ft_msg_and_exit()
{
	ft_putstr_fd("Fatal error. exit\n", 2);//errorメッセージはこれで統一。楽だから。
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
