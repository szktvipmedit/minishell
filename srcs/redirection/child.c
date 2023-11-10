#include "../../incs/minishell.h"

char	*find_command(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}



void child(t_node *parse_node, t_env_info env_info, char **envp, int parse_idx)
{
    t_redirect_node *redirect;
    redirect = parse_node->redirect;
    if(parse_node->type == INPUT || parse_node->type == HEREDOC)
    {
        dup2(redirect->pipe_fd[1], 1);
        close(redirect->pipe_fd[0]);
        dup2(redirect->target_fd, 0);
    }
    else if(parse_node->type == OUTPUT || parse_node->type == APPEND)
    {
    printf("    cmd path \n");
        dup2(parse_node->prev->redirect->pipe_fd[0], 0);
        close(parse_node->prev->redirect->pipe_fd[1]);
    printf("    cmd path \n");
        //notice: parse_idxが0の時ここにくるとsegmentation faultになる。そもそも1つ目からこの処理に辿り着くのか？
        // dup2(redirect->target_fd, 1);
        
    }
    redirect->split_cmd_args = ft_split(redirect->cmd_args, ' ');
    redirect->cmd_path = find_command(env_info.paths, redirect->split_cmd_args[0]);

    if(!redirect->cmd_path)
    {
        // child_clear();
        error_message("error");
    }
    execve(redirect->cmd_path, redirect->split_cmd_args, envp);
    
}