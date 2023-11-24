#include "minishell.h"

t_token	*ft_shift_node_location(t_token **token, size_t i)
{
	t_token	*tmp;
	size_t	index;

	tmp = *token;
	index = 0;
	while (tmp != NULL && index < i)
	{
		if (tmp->type == PIPE)
			index++;
		tmp = tmp->next;
	}
	return (tmp);
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
	char		**args;
	size_t	i;

	args = (char **)malloc(sizeof(char *) * (args_count + 1));
	if (args == NULL)
		ft_free_all_and_exit(shell);
	tmp = *node_head;
	i = 0;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
		{
			args[i] = ft_strdup(tmp->word);
			if (args[i] == NULL)
				ft_free_all_and_exit(shell);
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

t_redirect *ft_create_redirects(t_token **node_head, size_t redirects_count, t_shell *shell)
{
	t_redirect	*redirects;
	t_token			*tmp;
	size_t			i;

	if (redirects_count == 0)
		return (NULL);
	redirects = (t_redirect *)malloc(sizeof(t_redirect) * redirects_count);
	if (redirects == NULL)
		ft_free_all_and_exit(shell);
	tmp = *node_head;
	i = 0;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (tmp->type == INPUTFILE || tmp->type == OUTPUTFILE || tmp->type == DELIMITER || tmp->type == APPENDFILE)
		{
			redirects[i].target_name = ft_strdup(tmp->word);
			if (redirects[i].target_name == NULL)
				ft_free_all_and_exit(shell);
			redirects[i].type = tmp->type;
			i++;
		}
		tmp = tmp->next;
	}
	return (redirects);
}
