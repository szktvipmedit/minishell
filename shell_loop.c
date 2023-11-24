#include "minishell.h"

static void	ft_readline_error(t_shell *shell)//本家によせて"Fatal"なしで
{
	ft_free_strs(shell->environ_list_head);
	write(1, "exit\n", 5);
	exit(1);
}

static void	ft_delete_heredoc_file(t_node *node, t_shell *shell)
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
				ft_free_all_and_exit(shell);
		}
		i++;
	}
}

static void	ft_reset(t_shell *shell)
{
	ft_delete_heredoc_file(shell->node_head, shell);//nodeをfreeするまえに
	free(shell->line);
	shell->line = NULL;
	ft_free_token(shell->token_head);
	shell->token_head = NULL;//free後にexitするわけではないのでNULLづめする
	ft_free_node(shell->node_head, shell);
	shell->node_head = NULL;
}

// この関数内で受け取ったlineの全ての処理作業が行われる。
static void	ft_interpret_line(char *line, t_shell *shell)
{
	t_token	*token;
	t_node	*node;

	token = ft_tokenize(line, shell);
	if (shell->tokenize_error == -1)
	{
		shell->tokenize_error = 0;
		return;
	}
	if (ft_check_syntax(&token) == -1)
		return;
	node = ft_parse(&token, shell);
	ft_expand(node, shell);
	ft_heredoc(node, shell);//heredocを処理するのはメインプロセスであるためこのタイミング
	ft_execute(node, shell);
}

// whileループのみで構成されたminishellプログラムのメイン関数。
// エラーが発生するかシグナルが送られるまでループは終了しない。
void	ft_shell_loop(t_shell *shell)
{
	while (1)
	{
		ft_set_signal_handler(SHELL_LOOP);
		shell->line = readline("minishell$ ");
		if (shell->line == NULL)
			ft_readline_error(shell);
		else if (shell->line[0] == '\0')
			;
		else
		{
			add_history(shell->line);
			ft_interpret_line(shell->line, shell);
		}
		ft_reset(shell);
	}
}
