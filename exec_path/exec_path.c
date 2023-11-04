#include <stdio.h>
#include <unistd.h>
int confirm_exist_path(char *path)
{
	if(access(path, F_OK) == 0)
		return 1;
	return 0;
}

int exec_path(char *path, char **argv, char **envp)
{
	if(!confirm_exist_path(path))
		return (write(2, "このパスにコマンドはないのでとりあえず１返しとくよ\n", 27), 1);
	//今はオプションを考えないので、execveの第二引数にNULLを入れます
	execve(path, argv, envp);
	return 0;
}

int main(int argc, char **argv, char **envp)
{
	exec_path("/bin/pwd", argv, envp);
	return 0;
}