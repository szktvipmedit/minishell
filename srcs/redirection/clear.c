#include "../../incs/minishell.h"


void redirect_node_clear(t_redirect_node *redirect)
{
    close(redirect->target_fd);

}

void parent_clear(t_node *parse_node)
{
    t_redirect_node *redirect;

    redirect = parse_node->redirect;
    close(redirect->target_fd);
    if(parse_node->type == HEREDOC)
        unlink(".temp_heredoc");
    // free(redirect->cmd_args);
}