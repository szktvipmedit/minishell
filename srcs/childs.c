#include "../incs/pipex.h"

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

void	child_exe_cmd1(t_pipex *pipex, char **argv, char **envp)
{
	dup2(pipex->pipefd[1], 1);
	close(pipex->pipefd[0]);
	dup2(pipex->infile, 0);
	pipex->arg_cmd = ft_split(argv[2], ' ');
	pipex->cmd_path = find_command(pipex->paths, pipex->arg_cmd[0]);
	if (!pipex->cmd_path)
	{
		child_clear(pipex);
		error_message(CMD_NOT_FIND);
		exit(1);
	}
	execve(pipex->cmd_path, pipex->arg_cmd, envp);
}

void child_exe_cmd2(t_pipex *pipex, char **argv, char **envp)
{
	dup2(pipex->pipefd[0], 0);
	close(pipex->pipefd[1]);
	dup2(pipex->outfile, 1);
	pipex->arg_cmd = ft_split(argv[3], ' ');
	pipex->cmd_path = find_command(pipex->paths, pipex->arg_cmd[0]);
	if (!pipex->cmd_path)
	{
		child_clear(pipex);
		error_message(CMD_NOT_FIND);
		exit(1);
	}
	execve(pipex->cmd_path, pipex->arg_cmd, envp);
}