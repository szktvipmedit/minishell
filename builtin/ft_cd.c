#include "../minishell.h"

/*
操作メモ
    ..  ../ : ひとつ戻る
    / : ルートディレクトリ
    . : そのまま
    ~/  cdのみ: ホームディレクトリ
    
*/

t_list *create_path(char *buf)
{
    int i;
    int len;
    t_list *path_list;
    bool exist_list;

    i = 0;
    exist_list = false;
    while(buf[i])
    {
        len = 0;
        len = count_char_until_slash(i, buf);
        if(!exist_list)
        {
            path_list = ft_lstnew(ft_substr(buf, i, len));
            exist_list = true;
        }
        else
            ft_lstadd_back(&path_list, ft_lstnew(ft_substr(buf, i, len)));
        i = i + len;
    }
    return path_list;
}

static void del()
{
    return ;
}

static void rewrite_buf(t_list *arg_path_list, char *buf, char **envp)
{
    while(arg_path_list)
    {
        if(!ft_strncmp(arg_path_list->content, "~/", 3) || !ft_strncmp(arg_path_list->content, "~", 2))
            designated_home(buf, envp);
        else if(!ft_strncmp(arg_path_list->content, "..", 3) || !ft_strncmp(arg_path_list->content, "../", 4))
           designated_parent(buf);
        else if(!ft_strncmp(arg_path_list->content, "./", 3) || !ft_strncmp(arg_path_list->content, ".", 2))
            del();
        else if(!ft_strncmp(arg_path_list->content, "/", 2))
        {
            ft_bzero(buf, PATH_MAX);
            ft_strlcat(buf, "/", 2);
        }
        else{
            ft_strlcat(buf, "/", PATH_MAX);
            ft_strlcat(buf, arg_path_list->content, PATH_MAX);
        }
        arg_path_list = arg_path_list->next;
    }
}

static void chdir_designated(char **split_cmd_args, char **envp)
{
    char *buf;
    t_list *arg_path_list;

    buf = ft_calloc(PATH_MAX + 1, 1);
    getcwd(buf, PATH_MAX);
    arg_path_list = create_path(split_cmd_args[1]);
    rewrite_buf(arg_path_list, buf, envp); 
    if(chdir(buf) < 0)
        cd_error_message(arg_path_list);
    ft_lstclear(&arg_path_list, del);
    free(buf);
}

void ft_cd(char *cmd_args, char **envp)
{
    int argc;
    char **split_cmd_args;
    split_cmd_args = ft_split(cmd_args, ' ');
    argc = get_cmd_args_cnt(split_cmd_args);
    if(argc == 1)
        chdir(getenv_curr_env("HOME=", envp));
    else
        chdir_designated(split_cmd_args, envp);
    ft_split_all_free(split_cmd_args);
}