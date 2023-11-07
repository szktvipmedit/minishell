#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define STDERR 2

// error
# define ERR_INPUT "Error: Invalid arguments\n"
# define ERR_OPEN "Error: failed open()\n"
# define ERR_PIPE "Error: failed pipe()\n"
# define ERR_FORK "Error: failed fork()\n"
# define ERR_MALLOC "Error: failed malloc()\n"
# define ERR_PATH "Error: not found PATH\n"
# define CMD_NOT_FIND "command not found\n"

typedef struct s_pipex
{
	bool	is_heredoc;
	int		cmd_num;
	int		pipe_end_num;
	int		*pipe_ends;

	pid_t   child_pid;

	int		infile;
	int		outfile;

	char	**arg_cmd;
	char	*cmd_path;

	char	*path_addr;
	char	**paths;

}			t_pipex;

// path.c
char		*find_path_addr(char **envp);

// init.c
void		create_pipe(t_pipex *pipex);
void init_pipex(t_pipex *pipex, int argc, char **argv, char **envp);
// get_file.c
void		get_infile_case_default(t_pipex *pipex, char **argv);
void		get_infile_case_heredoc(t_pipex *pipex, char **argv);
void		get_infile(t_pipex *pipex, char **argv);
void		get_outfile(t_pipex *pipex, int argc, char **argv);

// childs.c
void child(t_pipex pipex, int pipe_idx, char **argv, char **envp);

// here_doc.c
int			is_there_heredoc(t_pipex *pipex, char *arg_may_have_heredoc);

// main.c

// clear.c
void all_close_pipes(t_pipex *pipex);
void		pipex_clear(t_pipex *pipex);
void		pipex_clear_by_get_paths(t_pipex *pipex);
void		child_clear(t_pipex *pipex);
void		parent_clear(t_pipex *pipex);

// error.c
void		error_message(char *error_message);

#endif