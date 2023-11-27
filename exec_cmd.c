#include "minishell.h"

static char	*ft_create_candidate_cmd(char *path_str, char *cmd, char **paths, t_shell *shell)
{
	char	*temp;
	char		*candidate_cmd;

	temp = ft_strjoin(path_str, "/");
	if (temp == NULL)
	{
		ft_free_strs(paths);
		ft_free_all_and_exit(shell, 1);
	}
	candidate_cmd = ft_strjoin(temp, cmd);
	if (candidate_cmd == NULL)
	{
		ft_free_strs(paths);
		free(temp);
		ft_free_all_and_exit(shell, 1);
	}
	free(temp);
	return (candidate_cmd);
}

static char *ft_search_cmd_from_path(char **paths, char *cmd, t_shell *shell)
{
	size_t	i;
	char		*candidate_cmd;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	i = 0;
	while(paths[i] != NULL)
	{
		candidate_cmd = ft_create_candidate_cmd(paths[i], cmd, paths, shell);
		if(access(candidate_cmd, X_OK) == 0)
			return (candidate_cmd);
		free(candidate_cmd);
		i++;
	}
	return (NULL);
}

static char	**ft_get_path_list(char **envp, t_shell *shell)
{
	char	**path_list;
	char	*path_addr;
	
	while(*envp != NULL && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (*envp == NULL)
		return (NULL);
	path_addr = *envp + 5;
	path_list = ft_split(path_addr, ':');
	if (path_list == NULL)
		ft_free_all_and_exit(shell, 1);
	return (path_list);
}

void	ft_execute_command(char **args, char **environ_list_head, t_shell *shell)
{
	char	**path_list;
	char	*cmd_path;
	char	*command;

	if (args[0] == NULL)
		ft_free_all_and_exit(shell, 0);
	path_list = ft_get_path_list(environ_list_head, shell);
	cmd_path = ft_search_cmd_from_path(path_list, args[0], shell);
	ft_free_strs(path_list);
	if (execve(cmd_path, args, environ_list_head) == -1)
	{
		free(cmd_path);
		command = ft_strdup(args[0]);
		if (command == NULL)
			ft_free_all_and_exit(shell, 1);
		ft_free_all_and_exit(shell, WITHOUT_EXIT);
		ft_printf_stderr("minishell: %s: command not found\n", command);
		free(command);
		exit(127);
	}
}
