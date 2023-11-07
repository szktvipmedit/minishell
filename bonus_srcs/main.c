#include "../incs/pipex_bonus.h"

void    create_prosess_to_execute_command(t_pipex *pipex, char **argv, char **envp)
{
    int pipe_idx;
    pipe_idx = 0;
    while(pipe_idx < pipex->cmd_num)
        child(*pipex, pipe_idx++, argv, envp);
}

int main(int argc, char **argv, char **envp)
{
    t_pipex pipex;

    if(argv[1] && argc < is_there_heredoc(&pipex, argv[1]))
        error_message(ERR_INPUT);
    init_pipex(&pipex, argc, argv, envp);

    //each_command_execute
    create_prosess_to_execute_command(&pipex, argv, envp);
    //pipe_close

    waitpid(-1, NULL, 0);
    parent_clear(&pipex);
    return 0;
}