#include "minishell.h"

static void	ft_get_exit_status(char **new_word, t_shell *shell)
{
	char	*tmp;
	char	*value;

	tmp = ft_itoa(g_exit_status);
	if (tmp == NULL)
		ft_free_all_and_exit(shell);
	value = tmp;
	while (*value != '\0')
		ft_append_char(new_word, *value++, shell);
	free(tmp);
}

static char	*ft_get_environ(char *src, char **env, t_shell *shell)
{
	size_t	i;
	char		*value;

	i = 0;
	value = NULL;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], src, ft_strlen(src)) == 0)
		{
			value = ft_strdup(env[i] + ft_strlen(src) + 1);//env_listの「変数名＝」以降をコピーする
			if (value == NULL)
				ft_free_all_and_exit(shell);
			break ;
		}
		i++;
	}
	return (value);
}

static void	ft_search_same_variable(char **new_word, char *src, t_shell *shell)
{
	char	*tmp;
	char	*value;

	if (*src == '?')
	{
		ft_get_exit_status(new_word, shell);
		return ;
	}
	tmp = ft_get_environ(src, shell->environ_list_head, shell); 
	value = tmp;
	if (value == NULL)
	{
		ft_append_char(new_word, '\0', shell);
		return ;
	}
	while (*value != '\0')
		ft_append_char(new_word, *value++, shell);
	free(tmp);
}

void	ft_dollar_to_environ(char **old_word, char **new_word, t_shell *shell)
{
	char	*src;

	src = ft_calloc(1, 1);
	if (src == NULL)
		ft_free_all_and_exit(shell);
	if (ft_create_src_variable(old_word, &src, shell) == 1)
	{
		ft_append_char(new_word, '$', shell);
		return ;
	}
	ft_search_same_variable(new_word, src, shell);
	free(src);
}
