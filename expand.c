#include "minishell.h"

static void	ft_create_expanded_str(char **old_word, char **new_word, t_shell *shell)
{
	while (**old_word != '\0')
	{
		if (**old_word == '\'')
			ft_remove_quotes(old_word, new_word, '\'', shell);
		else if (**old_word == '"')
			ft_remove_quotes(old_word, new_word, '"', shell);
		else if (**old_word == '$')
			ft_dollar_to_environ(old_word, new_word, shell);//環境変数の置き換えを行う。
		else
		{
			ft_append_char(new_word, **old_word, shell);//expand後の文字列を、一文字ずつ足していくかたちで作成。
			(*old_word)++;
		}
	}
}

static void	ft_replace_delimiter(char **delimiter, t_node *node, t_shell *shell)
{
	char	*old_word;
	char	*new_word;

	old_word = *delimiter;
	new_word = ft_calloc(1, 1);
	if (new_word == NULL)
		ft_free_all_and_exit(shell, 1);
	shell->expand_free_list[0] = new_word;
	while (*old_word != '\0')
	{
		if (*old_word == '\'')
		{
			ft_remove_delimiter_quotes(&old_word, &new_word, '\'', shell);
			node->delimiter_with_quote = 1;//heredoc実行時に入力値をexpandするべきかを判断する。
		}
		else if (*old_word == '"')
		{
			ft_remove_delimiter_quotes(&old_word, &new_word, '"', shell);
			node->delimiter_with_quote = 1;
		}
		else
			ft_append_char(&new_word, *old_word++, shell);
	}
	free(*delimiter);
	*delimiter = new_word;
}

static void	ft_replace_args(char **args, t_shell *shell)
{
	size_t	i;
	char		*old_word;
	char		*new_word;

	i = 0;
	while (args[i] != NULL)
	{
		old_word = args[i];
		new_word = ft_calloc(1, 1);
		if (new_word == NULL)
			ft_free_all_and_exit(shell, 1);
		shell->expand_free_list[0] = new_word;
		ft_create_expanded_str(&old_word, &new_word, shell);//共通の関数。
		free(args[i]);
		args[i] = new_word;
		ft_reset_expand_free_list(shell->expand_free_list);//こまめにfreeして再利用する。
		i++;
	}
}

static void	ft_replace_target_name(t_redirect	*redirects, t_node *node, t_shell *shell)
{
	size_t	i;
	char		*old_word;
	char		*new_word;

	i = 0;
	while (i < node->redirects_count)
	{
		if (redirects[i].type == DELIMITER)//delimiterに含まれる環境変数は展開しないという例外処理が必要
			ft_replace_delimiter(&redirects[i].target_name, node, shell);
		else
		{
			old_word = redirects[i].target_name;
			new_word = ft_calloc(1, 1);
			if (new_word == NULL)
				ft_free_all_and_exit(shell, 1);
			shell->expand_free_list[0] = new_word;
			ft_create_expanded_str(&old_word, &new_word, shell);//共通の関数。
			free(redirects[i].target_name);
			redirects[i].target_name = new_word;
		}
		ft_reset_expand_free_list(shell->expand_free_list);//こまめにfreeして再利用する。
		i++;
	}
}

void	ft_expand(t_node *node, t_shell *shell)
{
	size_t	i;

	i = 0;
	while (i < shell->node_count)
	{
		ft_replace_args(node[i].args, shell);
		ft_replace_target_name(node[i].redirects, &node[i], shell);//delimiterの例外処理以外はft_replace_argsとほぼ同じ。
		i++;
	}
}
