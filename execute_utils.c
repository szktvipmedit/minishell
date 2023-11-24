#include "minishell.h"

// bool	ft_is_builtin(char *arg)
// {
// 	if (arg == NULL)
// 		return (false);
// 	else if (ft_strcmp(arg, "echo") == 0)
// 		return (true);
// 	else if (ft_strcmp(arg, "cd") == 0)
// 		return (true);
// 	else if (ft_strcmp(arg, "pwd") == 0)
// 		return (true);
// 	else if (ft_strcmp(arg, "export") == 0)
// 		return (true);
// 	else if (ft_strcmp(arg, "unset") == 0)
// 		return (true);
// 	else if (ft_strcmp(arg, "env") == 0)
// 		return (true);
// 	else if (ft_strcmp(arg, "exit") == 0)
// 		return (true);
// 	else
// 		return (false);
// }

void	ft_exec_child(t_node node, t_shell *shell)
{
	ft_prepare_redirects(node, shell);
	ft_execute_command(node.args, shell->environ_list_head);
}
