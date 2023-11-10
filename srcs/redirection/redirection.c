#include "../../incs/minishell.h"

// void create_pipe(t_node *parse_node)
// {
//     if(pipe(parse_node->redirect->pipe_fd) < 0)
//         redirect_node_clear(parse_node->redirect);
// }


void redirection_init(t_node *parse_node)
{
    if(parse_node->type == INPUT || parse_node->type == HEREDOC)
        get_infile(parse_node);
    else if(parse_node->type == OUTPUT || parse_node->type == APPEND)
        get_outfile(parse_node->redirect);
    // create_pipe(parse_node);
    //notice: path_addrやpathsは全てのparseで使用するため、redirectionで宣言するのは不自然かも？
    // get_paths(parse_node); 
}

// void get_operator_idx(t_node *parse_node)
// {
//     t_token *arg;
//     int idx;
//     arg = parse_node->args;
//     idx = 0;
//     while(arg->type != OPERATOR)
//     {
//         idx++;
//         arg = arg->next;
//     }
//     parse_node->redirect->operator_idx = idx;
// }


void get_paths(t_env_info *env_info, char **envp)
{
    while(ft_strncmp(*envp, "PATH=", 5))
        envp++;
    
    env_info->path_addr = *envp + 5;

    env_info->paths = ft_split(env_info->path_addr, ':');
    if(!env_info->paths)
        error_message("path_error");
}

//perseされたnodeをひとつづつ参照し、リダイレクトしていく。
//パイプは次のstepなので、ここではoperatorを持つひとつのnode(parse)を渡される想定でredirect_typeに応じた条件分岐とそれらの処理を実装する
//前提：必ずparse_node->args[0]が存在し、args->type=operatorの要素が存在する.
//ファイル、コマンド、コマンドの適用先の判定が大変なので、一旦正しく判定し終えた状態を想定する
void redirection(t_node *parse_node, t_env_info env_info, char **envp, int parse_idx)
{
    // get_operator_idx(&parse_node);
    // if(redirection_args_check(&parse_node) == ERROR_INPUT)
    //     return;
    redirection_init(parse_node);
    printf("%i: redirection_init: ok\n", parse_idx);
    parse_node->redirect->pid = fork();
    if(parse_node->redirect->pid == 0)
        child(parse_node, env_info, envp, parse_idx);
    waitpid(parse_node->redirect->pid, NULL, 0);
    printf("%i: until parent_clear: ok\n", parse_idx);
    parent_clear(parse_node);
  
}
