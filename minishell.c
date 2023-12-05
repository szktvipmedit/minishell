#include "minishell.h"

static void	ft_terminal_setting(void)
{
	struct termios	term_settings;

	tcgetattr(2, &term_settings);
	term_settings.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSANOW, &term_settings);
}

static void	ft_initialize_shell(t_shell *shell)
{
	*shell = (t_shell){0};
}

static void	ft_clone_environ_list(t_shell *shell)
{
	extern char	**environ;
	char		**tmp;
	size_t		i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 1));
	if (tmp == NULL)
		ft_msg_and_exit();
	i = 0;
	while (environ[i] != NULL)
	{
		tmp[i] = ft_strdup(environ[i]);
		if (tmp[i] == NULL)
		{
			ft_free_strs(tmp);
			ft_msg_and_exit();
		}
		i++;
	}
	tmp[i] = NULL;
	shell->environ_list_head = tmp;
}

int	main(int argc, char **argv)
{
	t_shell	shell;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Usage: ./minishell\n", 2);
		exit(1);
	}
	ft_terminal_setting();
	ft_initialize_shell(&shell);
	ft_clone_environ_list(&shell);
	ft_increment_shlvl(&shell);
	ft_shell_loop(&shell);
	exit(0);
}
