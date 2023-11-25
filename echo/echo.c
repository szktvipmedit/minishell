#include "../../minishell.h"

/*
動かし方   
    execute.cを以下のように編集し、minishell.hとMakefileを調整する

void ft_exec_single_builtin(t_node *node, t_shell *shell, char *cmd_args)
{
	(void)node;
	(void)shell;
	if (ft_strncmp(cmd_args, "echo ", 5) == 0 || ft_strncmp(cmd_args, "echo", 5) == 0)
		echo(cmd_args);
    //今後増設
    

}
//nodeのwordはcmdの引数に関わるものなのでまとめる
char *ft_create_cmd_args(t_node *node)
{
    int i=0;
    char *cmd_args;
    // char *tmp;
    while(node->args[i])
    {
		if(i == 0)
			cmd_args = node->args[0];
		else
		{
			cmd_args = ft_strjoin(cmd_args, " ");//notice: leak
			cmd_args = ft_strjoin(cmd_args, node->args[i]);
		}
        i++;
    }
    return cmd_args;
}

static void	ft_exec_single_node(t_node	*node, t_shell *shell)
{
	pid_t	pid;
	int		status;
	
	if (ft_is_builtin(node[0].args[0]) == true)
	{
		char *cmd_args;
		cmd_args = ft_create_cmd_args(node);
		ft_prepare_redirects(*node, shell);
		ft_exec_single_builtin(node, shell, cmd_args);
		return ;
	}
	pid = fork();
	// if (pid == -1)
	// 	ft_error("fork");
	if (pid == 0)
		ft_exec_child(node[0], shell);
	waitpid(pid, &status, 0);
	// g_exit_status = WEXITSTATUS(status);
}
*/

static void output_strings(int i, bool option_flag, char **split_cmd_args[i])
{
    while(split_cmd_args[i])
    {
        printf("%s",split_cmd_args[i]);
        if(split_cmd_args[i+1])
            printf(" ");
        i++;
    }
    if(!option_flag)
        printf("\n");
}

static void prossesing_option_group(int *i, bool *option_flag, char **split_cmd_args)
{
    while(split_cmd_args[*i])
    {
        if(ft_strncmp(split_cmd_args[*i], "-n", 3))
            break;
        *option_flag = true;
        *i = *i+1;
    }
}

static void output(char **split_cmd_args)
{
    int i;
    bool option_flag = false;
    i = 1;
    prossesing_option_group(&i, &option_flag, split_cmd_args);
    output_strings(i, option_flag, split_cmd_args);
}

static int get_cmd_args_cnt(char **split_cmd_args)
{
    int argc;
    argc = 0;
    while(*split_cmd_args)
    {
        split_cmd_args++;
        argc++;
    }
    return argc;
}

int echo(char *cmd_args)
{
    int argc;
    char **split_cmd_args;
    split_cmd_args = ft_split(cmd_args, ' ');
    argc = get_cmd_args_cnt(split_cmd_args);
    if(argc == 1)
        printf("\n");
    else
        output(split_cmd_args);
    return 0;
}
