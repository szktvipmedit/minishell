#include "../incs/pipex_bonus.h"

static void count_cmd_num(t_pipex *pipex, int argc)
{
    pipex->cmd_num = argc - 3;
    if(pipex->is_heredoc)
        pipex->cmd_num -= 1;
}

static void create_pipe_basis(t_pipex *pipex)
{
    pipex->pipe_end_num = (pipex->cmd_num - 1) * 2;
    pipex->pipe_ends = malloc(sizeof(int) * pipex->pipe_end_num);
    if(!pipex->pipe_ends)
        error_message(ERR_MALLOC);
}

static void create_pipes(t_pipex *pipex, int argc)
{
    int i;
    i = 0;

    count_cmd_num(pipex, argc);
    create_pipe_basis(pipex);
    while(i < pipex->pipe_end_num - 1)
    {
        if(pipe(pipex->pipe_ends + i) <  0)
            pipex_clear(pipex);
        i = i + 2;
    }
}

static void get_paths(t_pipex *pipex, char **envp)
{
    while(ft_strncmp(*envp, "PATH=", 5))
        envp++;
    
    pipex->path_addr = *envp + 5;

    pipex->paths = ft_split(pipex->path_addr, ':');
    if(!pipex->paths)
        pipex_clear_by_get_paths(pipex);
}

void init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
    get_infile(pipex, argv);
    get_outfile(pipex, argc, argv); 
    create_pipes(pipex, argc);
    get_paths(pipex, envp);
    
}