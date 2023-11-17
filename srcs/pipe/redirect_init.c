#include "../../incs/minishell.h"

void get_outfile_output(t_node *parse_node, t_redirect_node *redirect)
{
    parse_node->outfile = open(redirect->target_filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
    if(parse_node->outfile < 0)
        error_message(ERROR_OPEN);
}

void get_outfile_append(t_node *parse_node, t_redirect_node *redirect)
{
    parse_node->outfile = open(redirect->target_filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
    if(parse_node->outfile < 0)
        error_message(ERROR_OPEN);
}

void get_outfile(t_node *parse_node)
{
    t_redirect_node *redirect;
    redirect = parse_node->redirect;
    while(redirect)
    {
        if(redirect->type == OUTPUT)
            get_outfile_output(parse_node, redirect);
        else if(redirect->type == APPEND)
            get_outfile_append(parse_node, redirect);
        redirect = redirect->next;
    }
}

void get_infile_heredoc(t_node *parse_node, t_redirect_node *redirect)
{
    int temp_fd;
    char *buf;
    temp_fd = open(".temp_heredoc", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(temp_fd < 0)
        error_message(ERROR_OPEN);
    while(1)
    {
        write(2, ">", 1);
        buf = get_next_line(0);
        if(!buf)
            perror("heredoc: get_infile_case_heredoc");
        buf[ft_strlen(buf) - 1] = '\0';
        if(!ft_strncmp(redirect->limiter, buf, ft_strlen(redirect->limiter) + 1))
        {
            free(buf);
            break;
        }
        write(temp_fd, buf, ft_strlen(buf));
        write(temp_fd, "\n", 1);
        free(buf);
    }
    close(temp_fd);
    parse_node->infile = open(".temp_heredoc", O_RDONLY);
    if(parse_node->infile < 0)
    {
        unlink(".temp_heredoc");
        error_message(ERROR_OPEN);
    }
}

void get_infile_input(t_node *parse_node, t_redirect_node *redirect)
{
    if(redirect->target_filename != NULL)
    {
        perror("get_infile_input: nothing target_filename");
        exit(1);
    }
    parse_node->infile = open(redirect->target_filename, O_RDONLY);
    if(parse_node->infile < 0)
        error_message(ERROR_OPEN);
}
void get_infile(t_node *parse_node)
{
    //input,heredocがないならline->pipe_fd[RD]を指したまま(0番目のparse以外ならば)だし、
    //output, appendがないならline->pipe_fd[WR]を指したまま(最後のparse以外ならば)になる
    t_redirect_node *redirect;
    redirect = parse_node->redirect;
    while(redirect)
    {
        if(redirect->type == INPUT)
            get_infile_input(parse_node, redirect);
        else if(redirect->type == HEREDOC)
            get_infile_heredoc(parse_node, redirect);
        redirect = redirect->next;
    }
}

void io_file_init(t_line *line, int parse_idx,  t_node *parse_node)
{
    if(parse_idx == 0)
    {
        parse_node->infile = 0;//notice: 標準入力でいいのかわからない。多分いいと思ってるけど.
        parse_node->outfile = line->pipe_fd[(parse_idx *2) + 1];
    }
    else if(parse_idx == line->pipe_cnt+1)
    {
        parse_node->infile = line->pipe_fd[(parse_idx * 2) - 2];
        parse_node->outfile = 1;
    }
    else
    {
        parse_node->infile = line->pipe_fd[(parse_idx * 2) - 2];
        parse_node->outfile = line->pipe_fd[(parse_idx *2) + 1];
    }
}

void redirect_init(t_line *line, t_node *parse_node)
{
    //infile,outfileをline->pipe_fd[そのparseが見るべき場所]に初期化する
    io_file_init(line, line->progress_parse_idx, parse_node);
    //そのparseはどこから入力を得るのか、redirectによる上書きを適用する
    get_infile(parse_node);
    //そのparseはどこに出力するのか、redirectによる上書きを適用する
    get_outfile(parse_node);
}