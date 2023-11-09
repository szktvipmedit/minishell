#include "../..//incs/minishell.h"

void error_message(char *error_message)
{
    write(STDERR, error_message, ft_strlen(error_message));
}
// int count_args_this_node(t_token *args)
// {
//     int arg_cnt;
//     arg_cnt = 0;
//     while(args)
//     {
//         arg_cnt++;
//         args = args->next;
//     }   
//     return arg_cnt;
// }

// void get_cmd(t_redirect_node *redirect, t_token *args)
// {
//     char *temp;
//     redirect->cmd_args = args->word;
//     while(args->next && args->next->type != OPERATOR)
//     {
//         args = args->next;
//         temp = ft_strjoin(redirect->cmd_args, " ");
//         redirect->cmd_args = ft_strjoin(temp, args->word);
//     }
// }
// static int input_args_check(t_node *parse_node)
// {
//     t_token *args;
//     t_redirect_node *redirect;
//     args = parse_node->args;
//     redirect = parse_node->redirect;

//     if(redirect->operator_idx == 0)
//     {
//         redirect->target_filename = args[1].word;
//         get_cmd(parse_node->redirect, parse_node->args[])
//     }
//     else

// }

// static int heredoc_args_check(t_node *parse_node)
// {
//     int i;
//     i = 0;
//     int arg_cnt;
//     arg_cnt = count_args_this_node(parse_node->args);
//     // printf("debug: arg_cnt = %i\n", arg_cnt);
//     if(arg_cnt == 1)
//         return (write(2, ERROR_NEWLINE, ft_strlen(ERROR_NEWLINE)), ERROR_INPUT);
//     if(arg_cnt == 2 && !ft_strncmp(parse_node->args[1].word, "<<", 3))
//         return (write(2, ERROR_NEWLINE, ft_strlen(ERROR_NEWLINE)), ERROR_INPUT);
//     return 0;
// }

// int redirection_args_check(t_node *parse_node)
// {
//     if(parse_node->type == INPUT)
//         return (input_args_check(parse_node));
//     else if(parse_node->type == OUTPUT)
//         return;   
//     else if(parse_node->type == HEREDOC)//input読み取り以前のエラーを弾く
//         return(heredoc_args_check(parse_node));
//     else if(parse_node->type == APPEND)
//     {

//     }
    
//     return 0;
// }