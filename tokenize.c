#include "minishell.h"

t_token	*ft_new_token(char *word, t_type type, t_shell *shell)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	if (token == NULL)
	{
		free(word);
		ft_free_all_and_exit(shell, 1);
	}
	if (shell->token_head == NULL)
		shell->token_head = token;
	token->word = word;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	ft_tokenize(char *line, t_shell *shell)
{
	t_token	head;
	t_token	*token;

	token = &head;
	while (*line != '\0')
	{
		if (*line == ' ' || *line == '\t')
			line++;
		else if (*line == '|' || *line == '<' || *line == '>')
		{
			token->next = ft_add_operator_token(&line, shell);
			token = token->next;
		}
		else
		{
			token->next = ft_add_word_token(&line, shell);
			token = token->next;
		}
	}
	if (shell->token_head == NULL)
		shell->tokenize_error = -1;
}
