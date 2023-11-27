#include "minishell.h"

static void	ft_quotes_error(char **line, t_shell *shell)//今回は実装しない
{
	ft_putstr_fd("Sorry, minishell does not support unclosed quotes.\n", 2);
	while (**line != '\0')
		(*line)++;
	shell->tokenize_error = -1;
}

static bool	ft_check_quote_closed(char **line, char quote_type)
{
	(*line)++;
	while (**line != '\0' && **line != quote_type)
		(*line)++;
	if (**line == '\0')
		return (false);
	else
		(*line)++;
	return (true);
}

static int	ft_skip_word_part(char **line)
{
	while (**line != '\0' && **line != ' ' && **line != '\t' && **line != '|' && **line != '<' && **line != '>')
	{
		if (**line == '\'')
		{
			if (ft_check_quote_closed(line, '\'') == false)
				return (-1);
		}
		else if (**line == '"')
		{
			if (ft_check_quote_closed(line, '"') == false)
				return (-1);
		}
		else
			(*line)++;
	}
	return (0);
}

t_token	*ft_add_word_token(char **line, t_shell *shell)
{
	char	*start;
	char	*word;

	start = *line;
	if (ft_skip_word_part(line) == -1)
		ft_quotes_error(line, shell);
	word = ft_strndup(start, *line - start);
	if (word == NULL)
		ft_free_all_and_exit(shell, 1);
	return (ft_new_token(word, WORD, shell));
}
