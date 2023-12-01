#include "../minishell.h"

void cd_error_message(t_list *arg_list)
{
    printf("minishell: cd: ");
    while(arg_list)
    {
        printf("%s", (char *)arg_list->content);
        arg_list = arg_list->next;
    }
    printf(": No such file or directory\n");
}

int count_char_until_slash(int i, char *buf)
{
    int len;
    int j;

    len = 0;
    j = i;
    while(buf[j] && buf[j] != '/')
    {
        len++;
        j++;
    }
    len++;
    return len;
}

void designated_home(char *buf, char **envp)
{
    char *homedir;
    homedir = getenv_curr_env("HOME=", envp);
    ft_bzero(buf, PATH_MAX);
    ft_strlcat(buf, homedir, PATH_MAX);
}

void designated_parent(char *buf)
{
    int len;
    len = ft_strlen(buf);
    if(!len)
        return;
    while(len >= 0)
    {
        if(*(buf + len - 1) == '/')
        {
            ft_bzero(buf + len - 1, 1);
            break; 
        }
        else
            ft_bzero(buf + len - 1, 1);
        len--;
    }
}