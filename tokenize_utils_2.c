#include "minishell.h"

static void	ft_quotes_error(char **resume, char *line, t_shell *shell)
{
	ft_putstr_fd("Error: minishell does not support unclosed quotes.\n", 2);
	while (*line)
		line++;
	*resume = line;
	shell->tokenize_error = -1;//shell構造体は初期値０だから、それを１に変える。
	g_exit_status = 0;//本家bashはエラー扱いにしないため、0に設定しておく。
}

static bool	ft_check_single_quote_closed(char **line)
{
	(*line)++;
	while (**line != '\0' && **line != '\'')
		(*line)++;
	if (**line == '\0')
		return (false);
	else
		(*line)++;
	return (true);
}

static bool	ft_check_double_quote_closed(char **line)
{
	(*line)++;
	while (**line != '\0' && **line != '"')
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
			if (ft_check_single_quote_closed(line) == false)
				return (-1);
		}
		else if (**line == '"')
		{
			if (ft_check_double_quote_closed(line) == false)
				return (-1);
		}
		else
			(*line)++;
	}
	return (0);
}

t_token	*ft_add_word_token(char **resume, char *line, t_shell *shell)
{
	char	*start;
	char	*word;

	start = line;
	if (ft_skip_word_part(&line) == -1)
		ft_quotes_error(resume, line, shell);
	*resume = line;
	word = ft_strndup(start, *resume - start);
	if (word == NULL)
		ft_free_all_and_exit(shell);
	return (ft_new_token(word, WORD, shell));
}
