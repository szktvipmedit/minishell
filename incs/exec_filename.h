#ifndef EXEC_FILENAME_H
 #define EXEC_FILENAME_H

// #include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#define STDERR 2
#define MINISHELL "minishell: "
#define NOT_FOUND_CMD "command not found\n"

void exec_filename(char *cmd, char **envp);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);

#endif