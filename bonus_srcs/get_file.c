#include "../incs/pipex_bonus.h"

void get_outfile(t_pipex *pipex, int argc, char **argv)
{
    pipex->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
    if(pipex->outfile < 0)
        error_message(ERR_OPEN);
}

void get_infile_case_heredoc(t_pipex *pipex, char **argv)
{
    int temp_fd;
    char *buf;
    temp_fd = open(".temp_heredoc", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(pipex->infile < 0)
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
    pipex->infile = open(".temp_heredoc", O_RDONLY);
    if(pipex->infile < 0)
    {
        unlink(".temp_heredoc");
        error_message(ERR_OPEN);
    }
}

void get_infile_case_default(t_pipex *pipex, char **argv)
{
    pipex->infile = open(argv[1], O_RDONLY);
    if(pipex->infile < 0)
        error_message(ERR_OPEN);

}

void  get_infile(t_pipex *pipex, char **argv)
{
    if(pipex->is_heredoc)
        get_infile_case_heredoc(pipex, argv);        
    else
        get_infile_case_default(pipex, argv);
}