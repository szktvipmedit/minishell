#include "../../incs/minishell.h"

// void pipe_all_close(t_node *parse_node)
// {

// }

void create_pipes(t_node *parse_node)
{
    while(parse_node)
    {
        if(pipe(parse_node->redirect->pipe_fd) < 0)
            perror("pipe error\n");
        parse_node = parse_node->next;
    }
}

int ft_pipe(t_node *parse_node, t_env_info env_info, char **envp)
{
    int parse_idx;
    parse_idx = 0;
    create_pipes(parse_node);
    //notice: [cat file |]のように、パイプで終わるlineを実行すると入力待ち状態になるので、それも実装する
    while(parse_node)
    {
        
        // printf("%s\n",);
        if(parse_node->type == COMMAND)
            printf("command\n");
        // {
        //     // exec_path()
        // }
        else
        {
            redirection(parse_node, env_info ,envp, parse_idx);
        }
        parse_node = parse_node->next;
        parse_idx++;
    }
    // pipe_all_close();
    return 0;
}