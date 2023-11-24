#include "minishell.h"

static char *ft_search_cmd_from_path(char **paths, char *cmd)
{
	size_t	i;
	char		*temp;
	char		*candidate_cmd;

	i = 0;
	while(paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		candidate_cmd = ft_strjoin(temp, cmd);
		free(temp);
		if(access(candidate_cmd, X_OK) == 0)
			return (candidate_cmd);
		free(candidate_cmd);
		i++;
	}
	// error_message(cmd);
	return (NULL);
}

static char	**ft_get_path_list(char **envp)
{
	char	*path_addr;
	
	while(ft_strncmp(*envp, "PATH=", 5))
		envp++;
	path_addr = *envp + 5;
	return (ft_split(path_addr, ':'));
}

void	ft_execute_command(char **args, char **environ_list_head)
{
	char	**path_list;
	char	*cmd_path;

	if (args[0] == NULL)
	{
		// ft_error_free
		exit(0);
	}
	path_list = ft_get_path_list(environ_list_head);
	cmd_path = ft_search_cmd_from_path(path_list, args[0]);
	execve(cmd_path, args, environ_list_head);
	// if exe == -1
	// ft_error_free
}
