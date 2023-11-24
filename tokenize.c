#include "minishell.h"

t_token	*ft_new_token(char *word, t_type type, t_shell *shell)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	if (token == NULL)
		ft_free_all_and_exit(shell);
	token->word = word;
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*ft_tokenize(char *line, t_shell *shell)
{
	t_token	head;
	t_token	*token;

	head.next = NULL;
	token = &head;
	shell->token_head = head.next;
	while (*line)
	{
		if (*line == ' ' || *line == '\t')
			line++;
		else if (*line == '|' || *line == '<' || *line == '>')
		{
			token->next = ft_add_operator_token(&line, line, shell);
			token = token->next;
		}
		else
		{
			token->next = ft_add_word_token(&line, line, shell);
			token = token->next;
		}
	}
	return (head.next);
}
