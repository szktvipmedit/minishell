t_node	*ft_new_node(int type, t_node *prev)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(*node));
	node->type = type;
	node->prev = prev;
	return (node);
}

t_token	*ft_clone_token(t_token *token)
{
	char	*word;

	if (token->word == NULL)
		return (ft_new_token(NULL, token->type));
	word = ft_strdup(token->word);
	if (word == NULL)
		printf("strdup");
	return (ft_new_token(word, token->type));
}

void	ft_add_token(t_token **args, t_token *ft_new_token)
{
	if (*args == NULL)
	{
		*args = ft_new_token;
		return ;
	}
	ft_add_token(&(*args)->next, ft_new_token);
}

void	ft_add_node(t_node **node, t_node *new_node)
{
	if (*node == NULL)
	{
		*node = new_node;
		return ;
	}
	ft_add_node(&(*node)->next, new_node);
}

bool	ft_is_same_operator(t_token *token, char *word)
{
	if (token->type != OPERATOR)
		return (false);
	return (ft_strcmp(token->word, word) == 0);
}
