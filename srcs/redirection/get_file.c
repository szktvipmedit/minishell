#include "../../incs/minishell.h"

void get_outfile(t_redirect_node *redirect)
{
    redirect->target_fd = open(redirect->target_filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
    if(redirect->target_fd < 0)
        error_message(ERROR_OPEN);
}

void get_infile_case_heredoc(t_redirect_node *redirect)
{
    int temp_fd;
    char *buf;
    temp_fd = open(".temp_heredoc", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(redirect->target_fd < 0)
        error_message(ERROR_OPEN);
    while(1)
    {
        write(2, ">", 1);
        buf = get_next_line(0);
        if(!buf)
            exit(1);
        buf[ft_strlen(buf) - 1] = '\0';
        if(!ft_strncmp(redirect->target_filename, buf, ft_strlen(redirect->target_filename) + 1))
        {
            free(buf);
            break;
        }
        write(temp_fd, buf, ft_strlen(buf));
        write(temp_fd, "\n", 1);
        free(buf);
    }
    close(temp_fd);
    redirect->target_fd = open(".temp_heredoc", O_RDONLY);
    if(redirect->target_fd < 0)
    {
        unlink(".temp_heredoc");
        error_message(ERROR_OPEN);
    }
}

void get_infile_case_default(t_redirect_node *redirect)
{
    redirect->target_fd = open(redirect->target_filename, O_RDONLY);
    if(redirect->target_fd < 0)
        error_message(ERROR_OPEN);
}

void  get_infile(t_node *parser_node)
{
    if(parser_node->type == HEREDOC)
        get_infile_case_heredoc(parser_node->redirect);        
    else
        get_infile_case_default(parser_node->redirect);
}