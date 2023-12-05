#include "../minishell.h"

/*
操作メモ
	..  ../ : ひとつ戻る
	/ : ルートディレクトリ
	. : そのまま
	~/  cdのみ: ホームディレクトリ

*/

t_list	*create_path(char *buf)
{
	int		i;
	int		len;
	t_list	*path_list;
	bool	exist_list;

	i = 0;
	exist_list = false;
	while (buf[i])
	{
		len = 0;
		len = count_char_until_slash(i, buf);
		if (!exist_list)
		{
			path_list = ft_lstnew(ft_substr(buf, i, len));
			exist_list = true;
		}
		else
			ft_lstadd_back(&path_list, ft_lstnew(ft_substr(buf, i, len)));
		i = i + len;
	}
	return (path_list);
}

static void	rewrite_buf(t_list *arg_path_list, char *buf, char **envp)
{
	while (arg_path_list)
	{
		if (!ft_strncmp(arg_path_list->content, "~/", 3)
			|| !ft_strncmp(arg_path_list->content, "~", 2))
			designated_home(buf, envp);
		else if (!ft_strncmp(arg_path_list->content, "..", 3)
			|| !ft_strncmp(arg_path_list->content, "../", 4))
			designated_parent(buf);
		else if (!ft_strncmp(arg_path_list->content, "./", 3)
			|| !ft_strncmp(arg_path_list->content, ".", 2))
			;
		else if (!ft_strncmp(arg_path_list->content, "/", 2))
		{
			ft_bzero(buf, PATH_MAX);
			ft_strlcat(buf, "/", 2);
		}
		else
		{
			ft_strlcat(buf, "/", PATH_MAX);
			ft_strlcat(buf, arg_path_list->content, PATH_MAX);
		}
		arg_path_list = arg_path_list->next;
	}
}

static int	chdir_designated(char **args, char **envp, t_shell *shell)
{
	char		*buf;
	struct stat	stat_buf;
	t_list		*arg_path_list;

	buf = ft_calloc(PATH_MAX + 1, 1);
	if (!buf)
		ft_free_all_and_exit(shell, 1);
	getcwd(buf, PATH_MAX);
	arg_path_list = create_path(args[0]);
	rewrite_buf(arg_path_list, buf, envp);
	if (!buf[0])
		buf[0] = '/';
	if (chdir(buf) < 0)
		return (chdir_designated_failed(args, buf, &stat_buf, arg_path_list),
			1);
	buf_clean(buf);
	ft_change_envvar("PWD=", buf, shell);
	ft_lstclear(&arg_path_list, free);
	free(buf);
	return (0);
}

static void	chdir_home(t_shell *shell)
{
	char	*home_addr;

	home_addr = getenv_curr_env("HOME=", shell->environ_list_head);
	if (!home_addr)
	{
		ft_printf_stderr("minishell: cd: HOME not set\n");
		g_exit_status = 1;
	}
	else
	{
		if (chdir(getenv_curr_env("HOME=", shell->environ_list_head)) < 0)
			g_exit_status = 1;
		else
			ft_change_envvar("PWD=", getenv_curr_env("HOME=",
					shell->environ_list_head), shell);
	}
}

void	ft_cd(char **args, t_shell *shell)
{
	int argc;
	char oldpwd[PATH_MAX + 1];
	char *cmd_args;

	cmd_args = ft_create_cmd_args(args);
	if (getcwd(oldpwd, PATH_MAX + 1) == NULL)
		ft_free_all_and_exit(shell, 1);
	argc = get_cmd_args_cnt(args);
	if (argc == 0)
		chdir_home(shell);
	else
	{
		if (chdir_designated(args, shell->environ_list_head, shell))
			g_exit_status = 1;
	}
	ft_change_envvar("OLDPWD=", oldpwd, shell);
	free(cmd_args);
	return ;
}