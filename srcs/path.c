#include "../incs/pipex.h"

char *find_path_addr(char **envp)
{
    while(ft_strncmp(*envp, "PATH=", 5))
        envp++;
    return *envp + 5;
}