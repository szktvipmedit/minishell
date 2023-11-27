#include "minishell.h"

static void	ft_handler_sigint_in_heredoc(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	g_exit_status = 130;
}

static void	ft_handler_display_new_prompt(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

void	ft_set_signal_handler(t_type type)
{
	if (type == SHELL_LOOP)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_handler_display_new_prompt);
	}
	if (type == HEREDOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_handler_sigint_in_heredoc);
	}
	if (type == PARENT_PROCESS)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
	if (type == CHILD_PROCESS)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
}
