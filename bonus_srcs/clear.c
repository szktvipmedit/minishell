#include "../incs/pipex_bonus.h"

void all_close_pipes(t_pipex *pipex)
{
    int i;
    i = 0;
    while(i < pipex->pipe_end_num)
    {
        close(pipex->pipe_ends[i++]);
    }
}

void pipex_clear(t_pipex *pipex)
{
    int i;
    i = 0;
    close(pipex->infile);
    close(pipex->outfile);
    if(pipex->is_heredoc)
        unlink(".temp_heredoc");
    while(pipex->paths[i])
    {
        free(pipex->paths[i]);
        i++;
    }
    free(pipex->paths);
    // free(pipex->pipe_ends);
}

void pipex_clear_by_get_paths(t_pipex *pipex)
{
    close(pipex->infile);
    close(pipex->outfile);
    if(pipex->is_heredoc)
        unlink(".temp_heredoc");
    free(pipex->pipe_ends);
    error_message(ERR_PATH);
    exit(1);
}

void child_clear(t_pipex *pipex)
{
    int i;
    i = 0;
    while(pipex->arg_cmd[i])
        free(pipex->arg_cmd[i++]);
    free(pipex->arg_cmd);
}

void parent_clear(t_pipex *pipex)
{
    pipex_clear(pipex);
}