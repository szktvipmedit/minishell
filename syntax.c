#include "minishell.h"

//なるべくエラーメッセージを本家に寄せたが、>|みたいな入力の場合だけ少し変わる。例外処理も可能だが、わざわざするほどじゃない。
static int	ft_syntax_error(char *word)
{
	ft_printf("minishell: syntax error near unexpected token `%s'\n", word);
	g_exit_status = 2;
	return (-1);
}

static int	ft_pipe_error(void)
{
	ft_putstr_fd("Error: minishell does not support `|' without a following command.\n", 2);
	g_exit_status = 0;
	return (-1);
}

int	ft_check_syntax(t_token	**token)
{
	t_token	*tmp;

	tmp = *token;
	if (tmp->type == PIPE)
		return (ft_syntax_error(tmp->word));
	while (tmp != NULL)
	{
		if ((tmp->type == PIPE) && tmp->next == NULL)
			return (ft_pipe_error());
		else if ((tmp->type == REDIRECT) && tmp->next == NULL)
			return (ft_syntax_error("newline"));
		else if ((tmp->type == PIPE || tmp->type == REDIRECT) && tmp->next->type == PIPE)
			return (ft_syntax_error(tmp->next->word));
		else if (tmp->type == REDIRECT && tmp->next->type == REDIRECT)
			return (ft_syntax_error(tmp->next->word));
		tmp = tmp->next;
	}
	return (0);
}
