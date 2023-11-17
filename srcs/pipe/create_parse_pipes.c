#include "../../incs/minishell.h"

// void pipe_all_close(t_node *parse_node)
// {

// }

int get_parse_cnt(t_node *node)
{
    int parse_cnt;
    parse_cnt = 0;
    while(node)
    {
        parse_cnt++;
        node = node->next;
    }
    if(parse_cnt == 0)
    {
        perror("get_parse_cnt: parse_cntが0なのにここまできた");
        exit(1);
    }
    return parse_cnt;
}

// int get_pipe_cnt(t_line *line, char *line_str
// {
//     int i;
//     int line_len;
//     i = 0;
//     line_len = ft_strlen(line);
//     while(i++ < line_len - 2)
//         line++;
//     //meaning: [cat file |]のように、パイプで終わるlineを実行すると入力待ち状態になるので、その判定のためのbool値確保
//     if(!ft_strncmp(line, " |", 2))
//     {
//         line->is_wait_input = true;
//         return (get_parse_cnt(line->parse_node));
//     }
//     else
//     {
//         line->is_wait_input = false;
//         return (get_parse_cnt(line->parse_node) - 1);
//     }
    
// }


void create_pipes(t_line *line, t_node *parse_node)
{
    int i;
    i = 0;
    //notice: line->lineの文字列は終端に空白やtabがないものとする
    line->pipe_cnt = get_parse_cnt(parse_node) - 1;
    line->pipe_fd = malloc(sizeof(int) * (line->pipe_cnt - 1) * 2);
    if(!line->pipe_fd)
    {
        perror("create_pipes: malloc error");
        exit(1);
    }
    while(i < line->pipe_cnt)
    {
        if(pipe(line->pipe_fd + i) < 0)
        {
            perror("create_pipe: pipe()");
            exit(1);
        }
        i = i + 2;
    }
}
