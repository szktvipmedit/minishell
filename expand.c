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
			ft_dollar_to_environ(old_word, new_word, shell);
		else
		{
			ft_append_char(new_word, **old_word, shell);
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
			node->delimiter_with_quote = 1;
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

void	ft_replace_target(t_redirect	*redirects, t_node *node, t_shell *shell)//行数字数制限のためstatic外した。
{
	size_t	i;
	char		*old_word;
	char		*new_word;

	i = 0;
	while (i < node->redirects_count)
	{
		if (redirects[i].type == DELIMITER)
			ft_replace_delimiter(&redirects[i].target_name, node, shell);
		else
		{
			old_word = redirects[i].target_name;
			new_word = ft_calloc(1, 1);
			if (new_word == NULL)
				ft_free_all_and_exit(shell, 1);
			shell->expand_free_list[0] = new_word;
			ft_create_expanded_str(&old_word, &new_word, shell);
			if (new_word[0] == '\0')//redirectのtargetがexpandによってヌル文字になってしまった時の例外処理
				ft_target_name_is_empty(redirects[i].target_name, &new_word, shell);
			free(redirects[i].target_name);
			redirects[i].target_name = new_word;
		}
		ft_reset_expand_free_list(shell->expand_free_list);
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
		ft_replace_target(node[i].redirects, &node[i], shell);
		i++;
	}
}
