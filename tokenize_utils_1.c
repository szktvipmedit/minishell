#include "minishell.h"

static void	ft_double_pipe_error(char **resume, char *line, t_shell *shell)
{
	ft_putstr_fd("Error: minishell does not support `||'.\n", 2);
	while (*line)
		line++;
	*resume = line;
	shell->tokenize_error = -1;//shell構造体は初期値０だから、それを１に変える。
	g_exit_status = 0;//本家bashはエラー扱いにしないため、0に設定しておく。
}

static t_token	*ft_single_redirect_token(char **resume, char *line, char *operator, t_shell *shell)
{
	char	*word;

	word = ft_strdup(operator);
	if (word == NULL)
		ft_free_all_and_exit(shell);
	*resume = line + 1;
	return (ft_new_token(word, REDIRECT, shell));
}
//malloc失敗時のエラー処理追加による25行オーバーと、引数上限４つに対応したため、ほぼ似た関数２つになってしまった
static t_token	*ft_double_redirect_token(char **resume, char *line, char *operator, t_shell *shell)
{
	char	*word;

	word = ft_strdup(operator);
	if (word == NULL)
		ft_free_all_and_exit(shell);
	*resume = line + 2;
	return (ft_new_token(word, REDIRECT, shell));
}

t_token	*ft_add_operator_token(char **resume, char *line, t_shell *shell)
{
	size_t	i;
	char 		*word;

	i = 0;
	if (line[i] == '<' && line[i + 1] == '<')
		return (ft_double_redirect_token(resume, line, "<<", shell));
	if (line[i] == '>' && line[i + 1] == '>')
		return (ft_double_redirect_token(resume, line, ">>", shell));
	if (line[i] == '<')
		return (ft_single_redirect_token(resume, line, "<", shell));
	if (line[i] == '>')
		return (ft_single_redirect_token(resume, line, ">", shell));
	else
	{
		word = ft_strdup("|");
		if (word == NULL)
			ft_free_all_and_exit(shell);
		*resume = line + 1;
		if (line[i + 1] == '|')
			ft_double_pipe_error(resume, line, shell);
		return (ft_new_token(word, PIPE, shell));
	}
}
