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

static void	ft_replace_delimiter(char **delimiter, t_shell *shell)
{
	char	*old_word;
	char	*new_word;

	old_word = *delimiter;
	new_word = ft_calloc(1, 1);
	if (new_word == NULL)
		ft_free_all_and_exit(shell);
	while (*old_word != '\0')
	{
		if (*old_word == '\'')
			ft_remove_delimiter_quotes(&old_word, &new_word, '\'', shell);
		else if (*old_word == '"')
			ft_remove_delimiter_quotes(&old_word, &new_word, '"', shell);
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
			ft_free_all_and_exit(shell);
		ft_create_expanded_str(&old_word, &new_word, shell);
		free(args[i]);
		args[i] = new_word;
		i++;
	}
}

static void	ft_replace_target_name(t_redirect	*redirects, t_node node, t_shell *shell)
{
	size_t	i;
	char		*old_word;
	char		*new_word;

	i = 0;
	while (i < node.redirects_count)
	{
		if (redirects[i].type == DELIMITER)//delimiterは環境変数を展開しない例外処理が必要
		{
			ft_replace_delimiter(&redirects[i].target_name, shell);
		}
		else
		{
			old_word = redirects[i].target_name;
			new_word = ft_calloc(1, 1);
			if (new_word == NULL)
				ft_free_all_and_exit(shell);
			ft_create_expanded_str(&old_word, &new_word, shell);
			free(redirects[i].target_name);
			redirects[i].target_name = new_word;
		}
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
		ft_replace_target_name(node[i].redirects, node[i], shell);//delimiterの例外処理以外はft_replace_argsとほとんど同じ
		i++;
	}
}
