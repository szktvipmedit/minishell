#include "../../incs/minishell.h"

// void pipe_all_close(t_node *parse_node)
// {

// }

void exec_path(t_node *parse_node)
{
    printf("exec_path\n");
}

void exec_redirect(t_line *line, t_node *parse_node)
{
    //fork()の前に入出力先を決める
    redirect_init(line, parse_node);
    t_redirect_node *redirect;
    redirect = parse_node->redirect;
    while(redirect)
    {
        redirect->pid = fork();
        if(redirect->pid == 0)
            exec_path(line, parse_node, redirect);
        redirect = redirect->next;
    }
}

void parse_look(t_line *line, t_node *parse_node, t_shell shell)
{
    if(parse_node->type == COMMAND)
        //最初のparseでなければline->pipe_fd[(progress_parse_idx * 2)]から読み込む
        //  line->pipe_fd
        //最後のparseでない限りはline->pipe_fd[(progress_parse_idx * 2) + 1]に書き込む
        exec_path(line, parse_node);
    else
        //最後のparseでない限りはline->pipe_fd[(progress_parse_idx * 2) + 1]に書き込む
        exec_redirect(line, parse_node);

}

int ft_pipe(t_line *line, t_shell shell)
{
    t_node *parse_node;

    parse_node = line->parse_node;
    create_pipes(line);

    //parseをひとつずつ参照していく
    while(parse_node)
    {
        parse_look(line, parse_node, shell);
        parse_node = parse_node->next;
        if(parse_node)
            line->progress_parse_idx++;
    }
    // pipe_all_close();
    return 0;
}