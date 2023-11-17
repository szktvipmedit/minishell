#include "../../incs/minishell.h"
int confirm_exist_path(char *path)
{
	if(access(path, F_OK) == 0)
		return 1;
	return 0;
}

void close_all_pipes(t_line *line)
{
	int i;
	i = 0;
	while(i < line->pipe_cnt * 2)
	{
		close(line->pipe_fd[i]);
		i++;
	}
}
void exec_path(t_line *line, t_node *parse_node, t_shell shell)
{
	dup2(parse_node->infile, 0);
	dup2(parse_node->outfile, 1);
	close_all_pipes(line);
	if(!confirm_exist_path(parse_node->cmd_path))
		write(2, "このパスにコマンドはないのでとりあえず１返しとくよ\n", 27);
	//今はオプションを考えないので、execveの第二引数にNULLを入れます
	execve(parse_node->cmd_path, parse_node->split_cmd_args, shell.envp_copy);
}

// int main(int argc, char **argv, char **envp)
// {
// 	exec_path("/bin/pwd", argv, envp);
// 	return 0;
// }