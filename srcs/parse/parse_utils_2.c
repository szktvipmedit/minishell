static t_node	*ft_new_input_node(t_token **resume, t_token *token)
{
	t_node	*node;

	node = ft_new_node(INPUT, NULL);
	node->filename = ft_clone_token(token->next);
	node->target_fd = STDIN_FILENO;
	*resume = token->next->next;
	return (node);
}

static t_node	*ft_new_output_node(t_token **resume, t_token *token)
{
	t_node	*node;

	node = ft_new_node(OUTPUT, NULL);
	node->filename = ft_clone_token(token->next);
	node->target_fd = STDOUT_FILENO;
	*resume = token->next->next;
	return (node);
}

static t_node	*ft_new_heredoc_node(t_token **resume, t_token *token)
{
	t_node	*node;

	node = ft_new_node(HEREDOC, NULL);
	node->delimiter = ft_clone_token(token->next);
	node->target_fd = STDIN_FILENO;
	*resume = token->next->next;
	return (node);
}

static t_node	*ft_new_append_node(t_token **resume, t_token *token)
{
	t_node	*node;

	node = ft_new_node(APPEND, NULL);
	node->filename = ft_clone_token(token->next);
	node->target_fd = STDOUT_FILENO;
	*resume = token->next->next;
	return (node);
}

void	ft_store_node_element(t_node *node, t_token **resume, t_token *token)
{
	if (token->type == WORD)
	{
		ft_add_token(&node->args, ft_clone_token(token));
		token = token->next;
	}
	else if (ft_is_same_operator(token, "<") && token->next->type == WORD)
		ft_add_node(&node->redirects, ft_new_input_node(&token, token));
	else if (ft_is_same_operator(token, ">") && token->next->type == WORD)
		ft_add_node(&node->redirects, ft_new_output_node(&token, token));
	else if (ft_is_same_operator(token, "<<") && token->next->type == WORD)
		ft_add_node(&node->redirects, ft_new_heredoc_node(&token, token));
	else if (ft_is_same_operator(token, ">>") && token->next->type == WORD)
		ft_add_node(&node->redirects, ft_new_append_node(&token, token));
	else if (token->type == EOF)
	{
		ft_add_token(&node->args, ft_clone_token(token));
		token = NULL;
	}
	else
	{
		ft_parse_error(resume, token);
		return ;
	}
	*resume = token;
}
