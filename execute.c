#include "minishell.h"

static char *ft_create_cmd_args(t_node *node)
{
    int i;
    int len;
	i = 0;
	len = 0;

    char *cmd_args;
 	while(node->args[i])
		len += ft_strlen(node->args[i++]);
	cmd_args = ft_calloc((len + 1),  1);
	i = 0;
    while(node->args[i])
    {
		ft_strlcat(cmd_args, node->args[i], len+1);
        i++;
    }
	printf("strlcat: %s\n", cmd_args);
    return cmd_args;
}

void ft_exec_single_builtin(t_node *node, t_shell *shell)
{
	(void)node;
	(void)shell;
	char *cmd_args;
	cmd_args = ft_create_cmd_args(node);
	if (ft_strncmp(cmd_args, "echo ", 5) == 0 || ft_strncmp(cmd_args, "echo", 5) == 0)
		ft_echo(cmd_args);
	else if (ft_strncmp(cmd_args, "cd ", 3) == 0 || ft_strncmp(cmd_args, "cd", 3) == 0)
		ft_cd(node, shell, cmd_args, shell->environ_list_head);
	else if (ft_strncmp(cmd_args, "exit ", 5) == 0 || ft_strncmp(cmd_args, "exit", 5) == 0)
		ft_exit(cmd_args);
	else if (ft_strncmp(cmd_args, "export ", 7) == 0 || ft_strncmp(cmd_args, "export", 7) == 0)
		ft_export(cmd_args, shell->environ_list_head);
	else if (ft_strncmp(cmd_args, "env ", 4) == 0 || ft_strncmp(cmd_args, "env", 4) == 0)
		ft_env(cmd_args, shell->environ_list_head, node, shell);
	else if (ft_strncmp(cmd_args, "unset ", 6) == 0 || ft_strncmp(cmd_args, "unset", 6) == 0)
		ft_unset(cmd_args, shell->environ_list_head);
	else if (ft_strncmp(cmd_args, "pwd ", 4) == 0 || ft_strncmp(cmd_args, "pwd", 4) == 0)
		ft_pwd(cmd_args);
	free(cmd_args);
}

static void	ft_exec_single_node(t_node	*node, t_shell *shell)
{
	pid_t	pid;
	int		status;
	
	if (ft_is_builtin(node[0].args[0]) == true)
	{
		char *cmd_args;
		ft_prepare_redirects(*node, shell);
		ft_exec_single_builtin(node, shell);
		return ;
	}
	pid = fork();
	if (pid == -1)
		ft_free_all_and_exit(shell, 1);
	if (pid == 0)
		ft_exec_child(node[0], shell);
	waitpid(pid, &status, 0);
	ft_set_exit_status(status);
}

void	ft_execute(t_node	*node, t_shell *shell)
{
	ft_set_signal_handler(PARENT_PROCESS);
	if (shell->node_count == 1)
		ft_exec_single_node(node, shell);
	else
		ft_exec_multiple_nodes(node, shell);
}
