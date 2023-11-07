#include "../incs/pipex_bonus.h"

static char *find_path_inc_cmd(t_pipex *pipex, char *cmd)
{
    int i;
    i = 0;
    char *temp;
    char *path;
    while(pipex->paths[i])
    {
        temp = ft_strjoin(pipex->paths[i], "/");
        path = ft_strjoin(temp, cmd);
        free(temp);
        if(access(path, F_OK) == 0)
            return path;
        free(path);
        i++;
    } 
    return NULL;
}

static int get_cmd_arg_num(bool is_heredoc, int pipe_idx)
{
    int cmd_arg_num;
    cmd_arg_num = 0;
    if(is_heredoc)
        return  cmd_arg_num = 2 + 1 + pipe_idx;
    else
        return cmd_arg_num = 2 + pipe_idx;
}

static void find_command(t_pipex *pipex, char **argv, int pipe_idx)
{
    int cmd_arg_num;
    cmd_arg_num = get_cmd_arg_num(pipex->is_heredoc, pipe_idx);
    pipex->arg_cmd = ft_split(argv[cmd_arg_num], ' ');
    pipex->cmd_path = find_path_inc_cmd(pipex, pipex->arg_cmd[0]);
    if(!pipex->cmd_path)
    {
        child_clear(pipex);
        error_message(ERR_MALLOC);
        exit(1);
    }

}

void child(t_pipex pipex, int pipe_idx, char **argv, char **envp)
{
    pipex.child_pid = fork();
    if(pipex.child_pid < 0)
    {
        error_message(ERR_FORK);
        exit(1);
    }
    if(pipex.child_pid == 0)
    {
        if(pipe_idx == 0)
        {
            dup2(pipex.infile, 0);
            dup2(pipex.pipe_ends[1], 1);
        }
        else if(pipe_idx == pipex.pipe_end_num - 1)
        {
            dup2(pipex.pipe_ends[2 * pipe_idx - 2], 0);
            dup2(pipex.outfile, 1);
        }
        else
        {
            dup2(pipex.pipe_ends[2 * pipe_idx - 2], 0);
            dup2(pipex.pipe_ends[2 * pipe_idx + 1], 1);
        }
        all_close_pipes(&pipex);
        find_command(&pipex, argv, pipe_idx);
        
        execve(pipex.cmd_path, pipex.arg_cmd , envp); 
    }
}