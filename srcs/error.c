#include "../incs/pipex.h"

void    error_message(char *error_message)
{
    write(STDERR, error_message, ft_strlen(error_message));
}