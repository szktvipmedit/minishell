#include "../..//incs/minishell.h"

void get_outfile(t_redirect_node *redirectj, int argc, char **argv)
{
    redirect->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
    if(redirect->outfile < 0)
        error_message(ERR_OPEN);
}

void get_infile_case_heredoc(t_redirect_node *redirectj, char **argv)
{
    int temp_fd;
    char *buf;
    temp_fd = open(".temp_heredoc", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(redirect->infile < 0)
        error_message(ERR_OPEN);
    while(1)
    {
        buf = get_next_line(0);
        if(!buf)
            exit(1);
        buf[ft_strlen(buf) - 1] = '\0';
        if(!ft_strncmp(argv[2], buf, ft_strlen(argv[2]) + 1))
        {
            free(buf);
            break;
        }
        write(temp_fd, buf, ft_strlen(buf));
        write(temp_fd, "\n", 1);
        free(buf);
    }
    close(temp_fd);
    redirect->infile = open(".temp_heredoc", O_RDONLY);
    if(redirect->infile < 0)
    {
        unlink(".temp_heredoc");
        error_message(ERR_OPEN);
    }
}

void get_infile_case_default(t_node *parse_node)
{
    
    if(ft_strncmp(parse_node->args[0].word, "<", 2) || ft_strncmp(parse_node->args[0].word, ">", 2) ||ft_strncmp(parse_node->args[0].word, "<<", 3) ||ft_strncmp(parse_node->args[0].word, ">>", 3))

    parse_node->redirect->infile = open(argv[1], O_RDONLY);
    if(parse_node->redirect->infile < 0)
        error_message(ERR_OPEN);

}

void  get_infile(t_node *parse_node)
{
    if(parse_node->type == HEREDOC)
        get_infile_case_heredoc(parse_node);        
    else
        get_infile_case_default(parse_node);
}