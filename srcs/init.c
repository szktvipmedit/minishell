#include "../incs/pipex.h"

void get_infile(t_pipex *pipex, char *infile)
{
    pipex->infile = open(infile, O_RDONLY);
    if(pipex->infile < 0)
        error_message(ERR_OPEN);
}

void get_outfile(t_pipex *pipex, char *outfile)
{
    pipex->outfile = open(outfile, O_TRUNC | O_CREAT | O_RDWR, 0000644);
    if(pipex->outfile < 0)
        error_message(ERR_OPEN);
}

void create_pipe(t_pipex *pipex)
{
    if(pipe(pipex->pipefd) < 0)
        error_message(ERR_PIPE);
}