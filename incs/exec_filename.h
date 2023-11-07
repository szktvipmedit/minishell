#ifndef EXEC_FILENAME_H
 #define EXEC_FILENAME_H

// #include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#define STDERR 2
#define MINISHELL "minishell: "
#define NOT_FOUND_CMD "command not found\n"

typedef struct s_exec_cmd_info
{
    pid_t child_pid;
    int pipe_fd[2];
    char **arg_cmds;
    char **paths;
    char *cmd_path;
}              t_exec_cmd_info;

void exec_filename(char *cmd, char **envp);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);

#endif