#include "../../incs/minishell.h"



void redirection_init(t_node *parse_node)
{
    get_infile();
    get_outfile();
    create_pipes();
    get_paths(); 
}


//perseされたnodeをひとつづつ参照し、リダイレクトしていく。
//パイプは次のstepなので、ここではひとつのnode(parse)を渡される想定でredirect_typeに応じた条件分岐とそれらの処理を実装する
void redirection_hub(t_node parse_node)
{
    redirection_init(&parse_node);

    if(parse_node.type == INPUT)
        redirect_input(parse_node);
    if(parse_node.type == OUTPUT)
        redirect_output();
    if(parse_node.type == HEREDOC)
        redirect_heredoc();
    if(parse_node.type == APPEND)
        redirect_append();
}
