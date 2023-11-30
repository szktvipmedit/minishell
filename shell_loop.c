#include "minishell.h"

static void	ft_readline_error(t_shell *shell)
{
	ft_free_strs(shell->environ_list_head);
	write(1, "exit\n", 5);
	exit(g_exit_status);
}

static void	ft_reset(t_shell *shell)
{
	char	**tmp;

	ft_delete_heredoc_file(shell->node_head, shell);
	free(shell->line);
	ft_free_token(shell->token_head);
	ft_free_node(shell->node_head, shell);
	tmp = shell->environ_list_head;
	*shell = (t_shell){0};
	shell->environ_list_head = tmp;
}

static void	ft_interpret_line(char *line, t_shell *shell)
{
	ft_tokenize(line, shell);
	if (shell->tokenize_error == -1)
		return;
	if (ft_check_syntax(shell->token_head) == -1)
		return;
	ft_parse(shell->token_head, shell);
	ft_expand(shell->node_head, shell);
	ft_heredoc(shell->node_head, shell);
	if (shell->heredoc_error == -1)
		return;
	ft_execute(shell->node_head, shell);
}

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
