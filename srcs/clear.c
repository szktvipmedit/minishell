#include "../incs/pipex.h"

void	child_clear(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->arg_cmd[i])
	{
		free(pipex->arg_cmd[i]);
		pipex->arg_cmd++;
	}
	free(pipex->arg_cmd);
	// free(pipex->cmd_path);
}

void	parent_clear(t_pipex *pipex)
{
	int i;
    i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	while (pipex->paths[i])
	{
		free(pipex->paths[i]);
		i++;
	}
	free(pipex->paths);
}