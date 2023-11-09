#include "../../incs/minishell.h"


void redirect_node_clear(t_redirect_node *redirect)
{
    close(redirect->target_fd);

}

void parent_clear(t_redirect_node *redirect)
{
    close(redirect->target_fd);
    // free(redirect->cmd_args);
}