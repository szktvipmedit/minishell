#include "minishell.h"

t_token	*ft_shift_node_location(t_token *token, size_t i)
{
	size_t	index;

	index = 0;
	while (token != NULL && index < i)
	{
		if (token->type == PIPE)
			index++;
		token = token->next;
	}
	return (token);
}

size_t	ft_count_args(t_token **node_head)
{
	t_token	*tmp;
	size_t	args_count;

	tmp = *node_head;
	args_count = 0;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			args_count++;
		tmp = tmp->next;
	}
	return (args_count);
}

char	**ft_create_args(t_token **node_head, size_t args_count, t_shell *shell)
{
	t_token	*tmp;
	char	**args;
	size_t	i;

	args = (char **)malloc(sizeof(char *) * (args_count + 1));
	if (args == NULL)
		ft_free_all_and_exit(shell, 1);
	tmp = *node_head;
	i = 0;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
		{
			args[i] = ft_strdup(tmp->word);
			if (args[i] == NULL)
			{
				ft_free_strs(args);
				ft_free_all_and_exit(shell, 1);
			}
			i++;
		}
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}

size_t	ft_count_redirect(t_token **node_head)
{
	t_token	*tmp;
	size_t	redirect_count;

	tmp = *node_head;
	redirect_count = 0;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (tmp->type == REDIRECT)
			redirect_count++;
		tmp = tmp->next;
	}
	return (redirect_count);
}

t_redirect	*ft_redi(t_token **node_head, size_t redirects_count,
		t_shell *shell)
{
	t_redirect	*redirects;
	t_token		*tmp;
	size_t		i;

	redirects = (t_redirect *)malloc(sizeof(t_redirect) * redirects_count);
	if (redirects == NULL)
		ft_free_all_and_exit(shell, 1);
	tmp = *node_head;
	i = 0;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (ft_is_valid_as_redirect_type(tmp->type))
		{
			redirects[i].target_name = ft_strdup(tmp->word);
			if (redirects[i].target_name == NULL)
			{
				ft_free_redirects(redirects, redirects_count);
				ft_free_all_and_exit(shell, 1);
			}
			redirects[i].type = tmp->type;
			i++;
		}
		tmp = tmp->next;
	}
	return (redirects);
}
