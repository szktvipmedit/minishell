void	ft_parse_error(t_token **rest, t_token *token)
{
	printf("error");
	while (token && token->type != EOF)
		token = token->next;
	*rest = token;
}

static bool	ft_check_near_pipe(t_node *node, t_token *token)
{
	t_token	*tmp;

	if (node->args == NULL || token->next->type == EOF)
	{
		ft_parse_error(&token, token);
		return (false);
	}
	tmp = node->args;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->type != WORD)
	{
		ft_parse_error(&token, token);
		return (false);
	}
	return (true);
}

t_node	*ft_parse(t_token *token)
{
	t_node	*head;
	t_node	*node;

	node = ft_new_node(COMMAND, NULL);
	head = node;
	while (token != NULL && token->type != EOF)
	{
		if (ft_is_same_operator(token, "|") == true)
		{
			if (ft_check_near_pipe(node, token) == false)
				return (head);
			ft_add_token(&node->args, ft_new_token(NULL, EOF));
			ft_add_node(&node->next, ft_new_node(COMMAND, node));
			node = node->next;
			token = token->next;
		}
		else
			ft_store_node_element(node, &token, token);
	}
	ft_store_node_element(node, &token, token);
	return (head);
}
