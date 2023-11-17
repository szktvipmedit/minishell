#include "../../incs/minishell.h"

typedef struct s_redirect{
    pid_t pid;
    int pipe_fd[2];
    int infile;
    char **paths;
    char *cmd_path;
    char *cmd;
    char **arg_cmd;
    char *limiter;
} redirect;
char	*find_cmd_test(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}



void child_test(redirect *redirect, int id,char **envp)
{
    if(id == 1)
    {
        redirect->cmd = "cat";
        redirect->arg_cmd = ft_split(redirect->cmd, ' ');
    }
    if(id == 0)
    {
        dup2(redirect->pipe_fd[1], 1);
        dup2(redirect->infile, 0);
    }
    else 
    {
        dup2(redirect->pipe_fd[0], 0);
    }
    close(redirect->pipe_fd[0]);
    close(redirect->pipe_fd[1]);
    redirect->cmd_path = find_cmd_test(redirect->paths, redirect->cmd);
    if(!redirect->cmd_path)
    {
        return;
    }
    execve(redirect->cmd_path, redirect->arg_cmd, envp);
}

void exec(redirect *redirect, char **envp, int id)
{
    redirect->pid = fork();
    if(redirect->pid == 0)
    {
        child_test(redirect, id, envp);
    }
    
}
void get_infile_test(redirect *redirect)
{
    int temp_fd;
    char *buf;
    temp_fd = open(".temp_heredoc", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(redirect->infile < 0)
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
    redirect->infile = open(".temp_heredoc", O_RDONLY);
    if(redirect->infile < 0)
    {
        unlink(".temp_heredoc");
        error_message(ERROR_OPEN);
    }
}
void get_path(t_shell *shell, char **envp)
{
    while(ft_strncmp(*envp, "PATH=", 5))
        envp++;
    
    shell->path_addr = *envp + 5;

    shell->paths = ft_split(shell->path_addr, ':');
    if(!shell->paths)
        error_message("path_error");
}
/*
ここでは、
<< EOF | cd 
のように、パイプを用いてcdに渡すと引数(標準入力と混同しないように注意)として読み込むことができることを
加味した実装を目指すために,dup2(pipe_fd[0],0)に
cd ../minitalk
でいうところの"../minitalk"が入った状態でexecve()を実行するとパスを変更してくれるのかを検証した。

結論として不可能だった。そもそもcdは環境変数のPWDを書き換える処理だが、子プロセスでの環境変数の変更は親プロセスには引き継げない。
execve()は実行後にその呼び出しプロセスが終了してしまう特性上、fork()によって子プロセスを作成することが必要だと思い込んでいた。
ただ、使用可能関数：chdir()はPWDを書き換える関数なので、execve()は使わなくて良さそうだ。

よって、現状考えられる方法として、パイプで入力を受け取る際には標準入力かfork()で子プロセスに分岐する前に、
実行しようとしているコマンドが、標準入力を受け取り可能かどうかによって条件自分木する必要があると考えられる
    標準入力も引数も対応   例)cat
        子プロセス内でdup2(pipe_fd[0], 0);としてexecve()を実行する
    引数しか対応できない(標準入力は無視)　 例)cd
        forkせずにpipe_fd[0]から文字列をgnlで読み込み、実行すべきコマンドと同じ挙動をするような関数に渡す。
*/
int main(int argc, char **argv, char **envp)
{
    int i = 0;
    t_shell shell;
    redirect redirect;
    pipe(redirect.pipe_fd);
    get_path(&shell,envp);
    redirect.paths = shell.paths;
    redirect.limiter = "EOF";
    while(i < 2)
    {
        if(i == 0)
            get_infile_test(&redirect);
        
        exec(&redirect, envp, i);
        waitpid(-1, NULL, 0);
        char *gnl = get_next_line(redirect.pipe_fd[0]);
        printf("gnlでpipe_fd[0]から読み取れるか %s\n", gnl);
        i++;
    }
    unlink(".temp_heredoc");
}