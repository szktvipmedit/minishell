#include "../../incs/minishell.h"
#include "../../incs/exec_filename.h"

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
	char **paths;
	char *cmd_path;
	char **arg_cmds;
	arg_cmds = ft_split(arg_cmd_block, ' ');
	paths = get_paths(envp);
	cmd_path = search_cmd_from_path(paths, arg_cmds[0]);
	if(!cmd_path)
		exit(1);
	execve(cmd_path, arg_cmds, envp);
	free(cmd_path);
}


//ひとつずつ試す
// int main(int argc, char **argv, char **envp)
// {
// 	exec_filename("pwd",  envp);
// 	// exec_filename("echo", argv, envp);
// 	// exec_filename("ls", argv, envp);
// 	// return 0;
// }


