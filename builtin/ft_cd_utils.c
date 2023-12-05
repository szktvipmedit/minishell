#include "../minishell.h"

void	cd_error_message(t_list *arg_list)
{
	ft_printf_stderr("minishell: cd: ");
	while (arg_list)
	{
		ft_printf_stderr("%s", (char *)arg_list->content);
		arg_list = arg_list->next;
	}
	ft_printf_stderr(": No such file or directory\n");
}

int	count_char_until_slash(int i, char *buf)
{
	int	len;
	int	j;

	len = 0;
	j = i;
	while (buf[j] && buf[j] != '/')
	{
		len++;
		j++;
	}
	len++;
	return (len);
}

void	designated_home(char *buf, char **envp)
{
	char	*homedir;

	homedir = getenv_curr_env("HOME=", envp);
	ft_bzero(buf, PATH_MAX);
	ft_strlcat(buf, homedir, PATH_MAX);
}

void	designated_parent(char *buf)
{
	int	len;

	len = ft_strlen(buf);
	if (!len)
		return ;
	while (len >= 0)
	{
		if (*(buf + len - 1) == '/')
		{
			ft_bzero(buf + len - 1, 1);
			break ;
		}
		else
			ft_bzero(buf + len - 1, 1);
		len--;
	}
}

void	buf_clean(char *buf)
{
	size_t i;
	size_t j;
	i = 0;
	j = 0;
	while (buf[i])
	{
		if (i > 0 && buf[i] == '/' && buf[i - 1] == '/')
		{
			j = i;
			while (buf[j])
			{
				buf[j] = buf[j + 1];
				j++;
			}
		}
		i++;
	}
}