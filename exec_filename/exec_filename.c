


//arg_cmd_block: "wc -c"のようなコマンドとそれに付随するオプションの塊
void exec_filename(char *cmd, char **arg_cmd_block, char **envp)
{
	char *path;
	path = search_cmd_from_path(cmd);
	execve(path, argv, envp);
	return 0;
}
