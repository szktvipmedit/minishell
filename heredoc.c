#include "minishell.h"

static char	*ft_expand_heredoc(char *buf, t_shell *shell)
{
	char	*new_word;

	new_word = ft_calloc(1, 1);//expand.cでやったことと、構造はほぼ同じ。
	if (new_word == NULL)
	{
		free(buf);
		ft_free_all_and_exit(shell, 1);
	}
	shell->expand_free_list[0] = new_word;
	shell->expand_free_list[4] = buf;//expand.cでは使用しなかったindex[4]を使用。複雑な構造の中、free漏れがないよう頑張った。
	while (*buf != '\0')
	{
		if (*buf == '$')
			ft_dollar_to_environ(&buf, &new_word, shell);//expand.cの関数の再利用。
		else
		{
			ft_append_char(&new_word, *buf, shell);//expand.cの関数の再利用。
			buf++;
		}
	}
	free(shell->expand_free_list[4]);
	shell->expand_free_list[4] = NULL;
	ft_reset_expand_free_list(shell->expand_free_list);//shell->expand_free_listはこまめにfreeして再利用する。
	return (new_word);
}

static char	*ft_create_temp_file(size_t node_index, t_shell *shell)
{
	char	*temp_file;
	char	*index_number;

	index_number = ft_itoa(node_index);
	if (index_number == NULL)
		ft_free_all_and_exit(shell, 1);
	temp_file = ft_strjoin(".temp_heredoc", index_number);//nodeごとに、".temp_heredoc0",".temp_heredoc1"を作成する。
	if (temp_file == NULL)
	{
		free(index_number);
		ft_free_all_and_exit(shell, 1);
	}
	free(index_number);
	return (temp_file);
}

static void	ft_heredoc_loop(t_node *node, char *delimiter, int temp_fd, t_shell *shell)
{
	char	*buf;

	while(1)
	{
		buf = readline("> ");//get_next_lineだと、ctrl+Dが入力された場合の処理が難しい
		if(buf == NULL)
		{
			ft_printf_stderr("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
			return ;
		}
		if (g_exit_status == 130)//ctrl+Cが押された
		{
			shell->heredoc_error = -1;
			return (free(buf));
		}
		if(ft_strcmp(buf, delimiter) == 0)
			return (free(buf));//25行制限のため、仕方なく
		if (node->delimiter_with_quote == 0)
			buf = ft_expand_heredoc(buf, shell);
		ft_putstr_fd(buf, temp_fd);
		ft_putstr_fd("\n", temp_fd);
		free(buf);
	}
}

static void	ft_search_heredoc(t_redirect	*redirects, t_node *node, size_t node_index, t_shell *shell)
{
	size_t	i;
	int			temp_fd;

	i = 0;
	while (i < node->redirects_count)
	{
		if (redirects[i].type == DELIMITER)
		{
			if (node->temp_file == NULL)
				node->temp_file = ft_create_temp_file(node_index, shell);
			temp_fd = open(node->temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(temp_fd == -1)
				ft_free_all_and_exit(shell, 1);
			ft_heredoc_loop(node, redirects[i].target_name, temp_fd, shell);
			close(temp_fd);
			if (shell->heredoc_error == -1)
				break;
		}
		i++;
	}
}

void	ft_heredoc(t_node *node, t_shell *shell)
{
	size_t	i;

	g_exit_status = 0;//heredoc後の終了ステータスは0か130の２択。heredoc_loopで130を条件文に使うため、ここでは0に設定しておく。
	ft_set_signal_handler(HEREDOC);
	i = 0;
	while (i < shell->node_count)
	{
		ft_search_heredoc(node[i].redirects, &node[i], i, shell);
		if (shell->heredoc_error == -1)
			break;
		i++;
	}
}
