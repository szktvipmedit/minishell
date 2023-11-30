#include "minishell.h"

static char *ft_create_cmd_args(t_node *node)
{
    int i;
    int len;
	i = 0;
	len = 0;

    char *cmd_args;
 	while(node->args[i])
	{
		len += ft_strlen(node->args[i++]) + 1;
		if(node->args[i])
			len++;
	}
	cmd_args = ft_calloc((len + 1),  1);
	i = 0;
    while(node->args[i])
    {
		ft_strlcat(cmd_args, node->args[i], len+1);
        i++;
		if(node->args[i])
			ft_strlcat(cmd_args, " ", len+1);
   }
    return cmd_args;
}

static void	ft_select_and_exec_cmd(t_node *node, char *cmd, char **args, t_shell *shell)
{
	char *cmd_args;
	cmd_args = ft_create_cmd_args(node);
	g_exit_status = 0;//コマンドは正常に実行されれば終了ステータスは0になるため、設定しておく。
	if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(args);//ft_echo内では変数shell使わない。
	else if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(cmd_args, shell);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd(shell);//ft_pwd内では変数shellしか使わない。
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(cmd_args, shell);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_unset(cmd_args, shell);
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(args, shell);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_exit(args, shell);
	free(cmd_args);
}

static void	ft_reset_std_fd(t_shell *shell)
{
	if (dup2(shell->std_fd[0], STDIN_FILENO) == -1)//dup2は第２引数がもし開いていたらcloseしてくれる。
		ft_free_all_and_exit(shell, 1);
	if (dup2(shell->std_fd[1], STDOUT_FILENO) == -1)
		ft_free_all_and_exit(shell, 1);
	if (close(shell->std_fd[0]) == -1)//dup関数で複製したため、closeが必要。
		ft_free_all_and_exit(shell, 1);
	if (close(shell->std_fd[1]) == -1)
		ft_free_all_and_exit(shell, 1);
}

static void	ft_store_std_fd(t_shell *shell)
{
	shell->std_fd[0] = dup(STDIN_FILENO);
	if (shell->std_fd[0] == -1)
		ft_free_all_and_exit(shell, 1);
	shell->std_fd[1] = dup(STDOUT_FILENO);
	if (shell->std_fd[1] == -1)
		ft_free_all_and_exit(shell, 1);
}

void	ft_exec_builtin(t_node node, t_shell *shell)
{
	ft_store_std_fd(shell);//1.stdinとstdoutのfdをdupで保存する。
	ft_prepare_redirects(node, shell);//2.stdinとstdoutをinfile,outfileにdup2で変更する。
	if (shell->single_node_builtin_error != -1)//上の関数でエラーが起きていなければ続行。
		ft_select_and_exec_cmd(&node, node.args[0], node.args + 1, shell);//第一引数はコマンド、第二引数はコマンド分を一つずらしたコマンドの引数。
	ft_reset_std_fd(shell);//3.stdinとstdoutをdupで保存したfdにdup2で戻す。dupしたものはcloseする。
}//forkした子プロセスなら必要ないが、親プロセスはstd_fdを元の状態に戻す必要がある。
