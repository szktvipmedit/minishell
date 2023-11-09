#include "../../incs/minishell.h"


t_token init_token(char *word, int type, t_token *next_token)
{
    t_token token;
    
    token.word = word;
    token.type = type;
    token.next = next_token;
    return token;
}

t_node init_parse(t_token *tokens, t_redirect_node *redirect,  int type, char *filename,char *cmd_args, char *limiter)
{
    t_node node;
    node.args = tokens;
    node.type = type;
    node.redirect = redirect;
    node.redirect->target_filename = filename;
    node.redirect->cmd_args = cmd_args;
    node.redirect->limiter = limiter;
    return node;
}

int main(int argc, char **argv, char **envp)
{
    t_env_info env_info;
    t_node node;
    t_redirect_node redirect;
    get_paths(&env_info, envp);

    t_token last_token = init_token("file2", WORD, NULL);
    t_token token = init_token("<<", OPERATOR, &last_token);
    t_token first_token = init_token("cat", WORD, &token);
    node = init_parse(&first_token,&redirect,  HEREDOC, "file2","cat", "file2");
    redirection(node, env_info, envp);
}