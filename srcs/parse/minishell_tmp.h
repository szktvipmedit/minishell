// # include <unistd.h>
# include "../../incs/minishell.h"
// # define COMMAND 0
// # define INPUT 1
// # define OUTPUT 2
// # define HEREDOC 3
// # define APPEND 4

typedef struct	s_node
{
	int						type;
	t_token				*args;
	struct s_node	*next;
	struct s_node	*prev;
	struct s_node	*redirects;
	int						target_fd;
	t_token				*filename;
	t_token				*delimiter;
}								t_node;

t_node	*ft_parse(t_token *token);
void		ft_parse_error(t_token **rest, t_token *token);

t_node	*ft_new_node(int type, t_node *prev);
t_token	*ft_clone_token(t_token *token);
void		ft_add_token(t_token **args, t_token *ft_new_token);
void		ft_add_node(t_node **node, t_node *new_node);
bool		ft_is_same_operator(t_token *token, char *word);

void		ft_store_node_element(t_node *node, t_token **resume, t_token *token);