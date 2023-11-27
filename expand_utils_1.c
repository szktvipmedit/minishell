#include "minishell.h"

void	ft_reset_expand_free_list(char **list)
{
	size_t	i;

	list[0] = NULL;//いつもexpand_free_list[0]に格納してるnew_wordのアドレスだけはargsに引き継いでいるためfreeしない。
	i = 1;
	while (i < 5)
	{
		if (list[i] != NULL)
		{
			free(list[i]);
			list[i] = NULL;
		}
		i++;
	}
}

static void	ft_get_exit_status(char **new_word, t_shell *shell)
{
	char	*status;

	status = ft_itoa(g_exit_status);//int型のexit_statusを文字列にする。
	if (status == NULL)
	{
		ft_free_strs(shell->expand_free_list);
		ft_free_all_and_exit(shell, 1);
	}
	shell->expand_free_list[2] = status;
	while (*status != '\0')
		ft_append_char(new_word, *status++, shell);
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
			{
				ft_free_strs(shell->expand_free_list);
				ft_free_all_and_exit(shell, 1);
			}
			break ;
		}
		i++;
	}
	return (value);
}

static void	ft_search_same_variable(char **new_word, char *src, t_shell *shell)
{
	char	*value;

	if (*src == '?')
	{
		ft_get_exit_status(new_word, shell);
		return ;
	}
	value = ft_get_environ(src, shell->environ_list_head, shell); 
	if (value == NULL)
	{
		ft_append_char(new_word, '\0', shell);
		return ;
	}
	shell->expand_free_list[3] = value;
	while (*value != '\0')
		ft_append_char(new_word, *value++, shell);
}

void	ft_dollar_to_environ(char **old_word, char **new_word, t_shell *shell)
{
	char	*src;

	src = ft_calloc(1, 1);
	if (src == NULL)
	{
		ft_free_strs(shell->expand_free_list);
		ft_free_all_and_exit(shell, 1);
	}
	shell->expand_free_list[1] = src;
	if (ft_create_src_variable(old_word, &src, shell) == 1)//環境変数に置き換えたい部分の文字列を作成。
	{
		ft_append_char(new_word, '$', shell);//ドルマークをただの一文字として作成。
		return ;
	}
	ft_search_same_variable(new_word, src, shell);//環境変数に置き換えたい部分と一致する文字列がenvリストにあるか探す。
	free(src);
	shell->expand_free_list[1] = NULL;
}
