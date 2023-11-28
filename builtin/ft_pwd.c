#include "../minishell.h"


void ft_pwd(char *cmd_args)
{
	// int argc;
	char *buf;
    char **split_cmd_args;
    split_cmd_args = ft_split(cmd_args, ' ');
	buf = ft_calloc(sizeof(char) * (PATH_MAX + 1),  1);
	getcwd(buf, PATH_MAX);
	printf("%s\n", buf);
	ft_split_all_free(split_cmd_args);
	return;
}
