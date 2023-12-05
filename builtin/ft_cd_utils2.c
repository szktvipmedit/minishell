#include "../minishell.h"

void	chdir_designated_failed(char **args, char *buf, struct stat *stat_buf,
		t_list *arg_path_list)
{
	if (stat(buf, stat_buf) || S_ISDIR(stat_buf->st_mode))
		cd_error_message(arg_path_list);
	else
		ft_printf_stderr("minishell: cd: %s: Not a directory\n", args[0]);
	ft_lstclear(&arg_path_list, free);
	free(buf);
}
