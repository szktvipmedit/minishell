#include "../../incs/minishell.h"


t_token init_token(char *word, int type, t_token *next_token)
{
    t_token token;
    
    token.word = word;
    token.type = type;
    token.next = next_token;
    return token;
}

t_node init_parse(t_token *tokens, t_redirect_node *redirect,  int type, char *filename,char *cmd_args, char *limiter, t_node *next_node)
{
    t_node node;
    node.args = tokens;
    node.type = type;
    node.redirect = redirect;
    node.redirect->target_filename = filename;
    node.redirect->cmd_args = cmd_args;
    node.redirect->limiter = limiter;
    node.next = next_node;
    return node;
}

int main(int argc, char **argv, char **envp)
{
    t_env_info env_info;
    get_paths(&env_info, envp);

    t_redirect_node redirect;
    t_token last_token1 = init_token("file2", WORD, NULL);
    t_token token1 = init_token(">", OPERATOR, &last_token1);
    t_token first_token1 = init_token("cat", WORD, &token1);
    t_node node1 = init_parse(&first_token1,&redirect,  OUTPUT, "file2","cat", "file2", NULL);

    t_token last_token = init_token("deli", WORD, NULL);
    t_token token = init_token("<<", OPERATOR, &last_token);
    t_token first_token = init_token("cat", WORD, &token);
    t_redirect_node redirect1;
    t_node node = init_parse(&first_token,&redirect1,  HEREDOC, NULL,"cat", "deli", &node1);


    ft_pipe(&node, env_info, envp);
}