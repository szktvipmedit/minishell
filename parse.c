#include "minishell.h"

static size_t	ft_count_node(t_token *token)
{
	size_t	node_count;

	node_count = 1;
	while (token != NULL)
	{
		if (token->type == PIPE)
			node_count++;
		token = token->next;
	}
	return (node_count);
}

static void	ft_change_token_type(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp != NULL)
	{
		if (tmp->type == REDIRECT)
		{
			if (ft_strncmp(tmp->word, "<<", 2) == 0)
				tmp->next->type = DELIMITER;
			else if (ft_strncmp(tmp->word, ">>", 2) == 0)
				tmp->next->type = APPENDFILE;
			else if (ft_strncmp(tmp->word, "<", 1) == 0)
				tmp->next->type = INPUTFILE;
			else if (ft_strncmp(tmp->word, ">", 1) == 0)
				tmp->next->type = OUTPUTFILE;
		}
		tmp = tmp->next;
	}
}

void	ft_parse(t_token *token, t_shell *shell)
{
	t_token	*node_head;
	t_node	*node;
	size_t	i;

	ft_change_token_type(&token);
	shell->node_count = ft_count_node(token);
	node = (t_node *)malloc(sizeof(t_node) * shell->node_count);
	if (node == NULL)
		ft_free_all_and_exit(shell, 1);
	shell->node_head = node;
	i = 0;
	while (i < shell->node_count)
	{
		node_head = ft_shift_node_location(token, i);
		node[i].args_count = ft_count_args(&node_head);
		node[i].args = ft_create_args(&node_head, node[i].args_count, shell);
		node[i].redirects_count = ft_count_redirect(&node_head);
		if (node[i].redirects_count == 0)
			node[i].redirects = NULL;
		else
			node[i].redirects = ft_create_redirects(&node_head, node[i].redirects_count, shell);
		node[i].temp_file = NULL;
		node[i].delimiter_with_quote = 0;
		i++;
	}
}
