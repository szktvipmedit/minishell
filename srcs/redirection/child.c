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



void child(t_node *parse_node, t_env_info env_info, char **envp)
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
        dup2(redirect->target_fd, 1);
        close(redirect->pipe_fd[1]);
        dup2(redirect->pipe_fd[0], 0);
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