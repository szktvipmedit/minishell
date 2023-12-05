#include "minishell.h"

void	ft_target_name_is_empty(char *target_name, char **new_word,
		t_shell *shell)
{
	char	*tmp;

	tmp = *new_word;
	*new_word = ft_strjoin("$?", target_name);
	if (*new_word == NULL)
		ft_free_all_and_exit(shell, 1);
	free(tmp);
}

int	ft_is_valid_as_redirect_type(t_type type) 
{
	return (type == INPUTFILE || type == OUTPUTFILE || type == DELIMITER
		|| type == APPENDFILE);
}

int	ft_is_amb(t_type type, char *target_name) 
{
	return (type == INPUTFILE && ft_strncmp(target_name, "$?", 2) == 0);
}

void	ft_put_exit_or_not(t_shell *shell)
{
	if (shell->is_multiple_node != 1)
		ft_putstr_fd("exit\n", 2);
}
