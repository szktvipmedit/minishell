#include "../../incs/minishell.h"
#include "../../incs/exec_filename.h"

void execve_cmd(t_exec_cmd_info *exec_cmd_info, char **envp)
{
	dup2(exec_cmd_info->pipe_fd[1], 1);
	close(exec_cmd_info->pipe_fd[0]);
	execve(exec_cmd_info->cmd_path, exec_cmd_info->arg_cmds, envp);
}

static void error_message(char *cmd)
{
	write(STDERR, MINISHELL, ft_strlen(MINISHELL));
	write(STDERR, cmd, ft_strlen(cmd));
	write(STDERR, ": ", 2);
	write(STDERR, NOT_FOUND_CMD, ft_strlen(NOT_FOUND_CMD));
}

static char **get_paths(char **envp)
{
	char *path_addr;
    while(ft_strncmp(*envp, "PATH=", 5))
        envp++;
	path_addr = *envp + 5;
    return (ft_split(path_addr, ':'));
}

static char *search_cmd_from_path(char **paths, char *cmd)
{
	int i;
	i = 0;
	char *temp;
	char *candidate_cmd;
	while(paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		candidate_cmd = ft_strjoin(temp, cmd);
		free(temp);
		if(access(candidate_cmd, F_OK) == 0)
			return candidate_cmd;
		free(candidate_cmd);
		i++;
	}

	error_message(cmd);
	return NULL;
}

//arg_cmd_block: "wc -c"のような、コマンドとオプションの塊
void exec_filename(char *arg_cmd_block, char **envp)
{
	t_exec_cmd_info exec_cmd_info;
	char buf[_MAX];	
	if(pipe(exec_cmd_info.pipe_fd) < 0)
		return;
	exec_cmd_info.arg_cmds = ft_split(arg_cmd_block, ' ');
	exec_cmd_info.paths = get_paths(envp);
	exec_cmd_info.cmd_path = search_cmd_from_path(exec_cmd_info.paths, exec_cmd_info.arg_cmds[0]);
	if(!exec_cmd_info.cmd_path)
		exit(1);//notice: error_message()?
	exec_cmd_info.child_pid = fork();
	if(exec_cmd_info.child_pid == 0)
		execve_cmd(&exec_cmd_info, envp);
	waitpid(-1, NULL, 0);
	if(read(exec_cmd_info.pipe_fd[0], buf, SIZE_MAX) < 0)
		exit(1);//notice: error_message()?
	printf("%s", buf);
	free(exec_cmd_info.cmd_path);
}


//ひとつずつ試す
// int main(int argc, char **argv, char **envp)
// {
// 	exec_filename("pwd",  envp);
// 	// exec_filename("echo", argv, envp);
// 	// exec_filename("ls", argv, envp);
// 	// return 0;
// }


