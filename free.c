#include "minishell.h"

void	ft_free_strs(char **strs)
{
	size_t	i;

	if (strs == NULL)
		return ;
	i = 0;
	while (strs[i] != NULL)
		free(strs[i++]);
	free(strs);
}

void	ft_free_token(t_token *token)
{
	t_token	*tmp;
	t_token	*next;

	if (token == NULL)
		return ;
	tmp = token;
	while (tmp != NULL)
	{
		if (tmp->word != NULL)
			free(tmp->word);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	ft_free_redirects(t_redirect *redirects, size_t redirects_count)
{
	size_t	i;

	if (redirects == NULL)
		return ;
	i = 0;
	while (i < redirects_count && redirects[i].target_name != NULL)
	{
		free(redirects[i].target_name);
		i++;
	}
	free(redirects);
}

void	ft_free_node(t_node *node, t_shell *shell)
{
	size_t	i;

	if (node == NULL)
		return ;
	i = 0;
	while (i < shell->node_count)
	{
		ft_free_strs(node[i].args);
		ft_free_redirects(node[i].redirects, node[i].redirects_count);
		if (node[i].temp_file != NULL)
			free(node[i].temp_file);
		i++;
	}
	free(node);
}
