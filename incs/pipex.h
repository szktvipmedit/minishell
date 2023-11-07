#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define STDERR 2

// error
# define ERR_INPUT "Error: Invalid arguments\n"
# define ERR_OPEN "Error: failed open()\n"
# define ERR_PIPE "Error: failed pipe()\n"
# define CMD_NOT_FIND "command not found\n"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;

	int		infile;
	int		outfile;

	char	**arg_cmd;
	char	*cmd_path;

	int		pipefd[2];
	char	*path_addr;
	char	**paths;
}			t_pipex;

// path.c
char		*find_path_addr(char **envp);

// init.c
void		get_infile(t_pipex *pipex, char *infile);
void		get_outfile(t_pipex *pipex, char *outfile);
void		create_pipe(t_pipex *pipex);

// childs.c
char		*find_command(char **paths, char *cmd);
void child_exe_cmd1(t_pipex *pipex, char **argv, char **envp);
void child_exe_cmd2(t_pipex *pipex, char **argv, char **envp);

// main.c

//clear.c
void child_clear(t_pipex *pipex);
void parent_clear(t_pipex *pipex);

// error.c
void		error_message(char *error_message);

#endif