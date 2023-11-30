#include "minishell.h"

void	ft_append_char(char **new_word, char c, t_shell *shell)
{
	size_t	size;
	char	*new;

	size = ft_strlen(*new_word) + 2;
	new = (char	*)malloc(sizeof(char) * size);
	if (new == NULL)
	{
		ft_free_strs(shell->expand_free_list);
		ft_free_all_and_exit(shell, 1);
	}
	ft_strlcpy(new, *new_word, size);
	new[size - 2] = c;
	new[size - 1] = '\0';
	free(*new_word);
	*new_word = new;
}

void	ft_remove_delimiter_quotes(char **old_word, char **new_word, char quote_type, t_shell *shell)
{
	(*old_word)++;
	if (**old_word == quote_type)
		ft_append_char(new_word, '\0', shell);
	else
	{
		while (**old_word != quote_type)
		{
			ft_append_char(new_word, **old_word, shell);
			(*old_word)++;
		}
	}
	(*old_word)++;
}

void	ft_remove_quotes(char **old_word, char **new_word, char quote_type, t_shell *shell)
{
	(*old_word)++;
	if (**old_word == quote_type)
		ft_append_char(new_word, '\0', shell);
	else
	{
		while (**old_word != quote_type)
		{
			if (**old_word == '$' && quote_type == '"')
				ft_dollar_to_environ(old_word, new_word, shell);
			else
			{
				ft_append_char(new_word, **old_word, shell);
				(*old_word)++;
			}
		}
	}
	(*old_word)++;
}

static int	ft_is_valid_as_initial_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || c == '?');
}

int	ft_create_src_variable(char **old_word, char **src, t_shell *shell)
{
	(*old_word)++;
	if (ft_is_valid_as_initial_char(**old_word) == 0)
		return (1);
	if (**old_word == '?')
	{
		ft_append_char(src, '?', shell);
		(*old_word)++;
		return (0);
	}
	while (**old_word != '\0' && (ft_is_valid_as_initial_char(**old_word) || (**old_word >= '0' && **old_word <= '9')))
	{
		ft_append_char(src, **old_word, shell);
		(*old_word)++;
	}
	return (0);
}
