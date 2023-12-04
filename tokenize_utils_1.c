#include "minishell.h"

static void	ft_specify_fd_error(char **line, t_shell *shell)
{
	ft_putstr_fd("Sorry, minishell does not support `[n]<', `[n]>', \
	`[n]<<',`[n]>>'.\n", 2);
	while (**line != '\0')
		(*line)++;
	shell->tokenize_error = -1;
}

static void	ft_force_overwrite_error(char **line, t_shell *shell)
{
	ft_putstr_fd("Sorry, minishell does not support `>|'.\n", 2);
	while (**line != '\0')
		(*line)++;
	shell->tokenize_error = -1;
}

static void	ft_double_pipe_error(char **line, t_shell *shell)
{
	ft_putstr_fd("Sorry, minishell does not support `||'.\n", 2);
	while (**line != '\0')
		(*line)++;
	shell->tokenize_error = -1;
}

static t_token	*ft_redirect_token(char **line, char *redirect, int word_len,
		t_shell *shell)
{
	char	*word;

	if (*line != shell->line && *(*line - 1) >= '0' && *(*line - 1) <= '9'
		&& **line != '\0')
		ft_specify_fd_error(line, shell);
	word = ft_strdup(redirect);
	if (word == NULL)
		ft_free_all_and_exit(shell, 1);
	*line = *line + word_len;
	return (ft_new_token(word, REDIRECT, shell));
}

t_token	*ft_add_operator_token(char **line, t_shell *shell)
{
	char	*word;

	if (**line == '<' && *(*line + 1) == '<')
		return (ft_redirect_token(line, "<<", 2, shell));
	if (**line == '>' && *(*line + 1) == '>')
		return (ft_redirect_token(line, ">>", 2, shell));
	if (**line == '<')
		return (ft_redirect_token(line, "<", 1, shell));
	if (**line == '>')
	{
		if (*(*line + 1) == '|')
			ft_force_overwrite_error(line, shell);
		return (ft_redirect_token(line, ">", 1, shell));
	}
	else
	{
		if (*(*line + 1) == '|')
			ft_double_pipe_error(line, shell);
		word = ft_strdup("|");
		if (word == NULL)
			ft_free_all_and_exit(shell, 1);
		(*line)++;
		return (ft_new_token(word, PIPE, shell));
	}
}
