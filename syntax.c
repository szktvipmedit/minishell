#include "minishell.h"

//なるべくエラーメッセージを本家に寄せたが、>|みたいな入力の場合だけ少し変わる。例外処理も可能だが、わざわざするほどじゃない。
static int	ft_syntax_error(char *word)
{
	ft_printf_stderr("minishell: syntax error near unexpected token `%s'\n", word);
	g_exit_status = 2;
	return (-1);
}

static int	ft_pipe_error(void)//今回は実装しない
{
	ft_putstr_fd("Sorry, minishell does not support `|' without a following command.\n", 2);
	return (-1);
}

int	ft_check_syntax(t_token	*token)
{
	if (token->type == PIPE)
		return (ft_syntax_error(token->word));
	while (token != NULL)
	{
		if ((token->type == PIPE) && token->next == NULL)
			return (ft_pipe_error());
		else if ((token->type == REDIRECT) && token->next == NULL)
			return (ft_syntax_error("newline"));
		else if ((token->type == PIPE || token->type == REDIRECT) && token->next->type == PIPE)
			return (ft_syntax_error(token->next->word));
		else if (token->type == REDIRECT && token->next->type == REDIRECT)
			return (ft_syntax_error(token->next->word));
		token = token->next;
	}
	return (0);
}
