#include "../incs/pipex_bonus.h"

int is_there_heredoc(t_pipex *pipex, char *arg_may_have_heredoc)
{
    if(!ft_strncmp("here_doc", arg_may_have_heredoc, 9))
    {
        pipex->is_heredoc = true;
        return 6;
    }
    else
    {
        pipex->is_heredoc = false;
        return 5;
    }
}

