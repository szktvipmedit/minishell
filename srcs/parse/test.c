#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

# define WORD 0
# define OPERATOR 1

typedef struct	s_shell
{
	bool					syntax_error;
}								t_shell;

typedef struct		s_token
{
	char						*word;
	int							type;
	struct s_token	*next;
}									t_token;

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void  *ptr;

	ptr = (void *)malloc(size * count);
	if (ptr == NULL)
		return (NULL);
  ft_bzero(ptr, (size * count));
	return (ptr);
}

t_token	*ft_new_token(char *word, int type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	token->word = word;
	token->type = type;
	return (token);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(src);
	i = 0;
	while (i < (dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (s_len);
}

char	*ft_strdup(char *s1)
{
  size_t	s_len;
	char		*dst;

	s_len = ft_strlen(s1);
	dst = (char *)malloc(sizeof(char) * (s_len + 1));
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, s1, (s_len + 1));
	return (dst);
}

static t_token	*ft_add_operator_token(char **resume, char *line)
{
	size_t	i;
	char 		*word;

	i = 0;
	if ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>'))
	{
		if (line[i] == '<')
			word = ft_strdup("<<");
		else
			word = ft_strdup(">>");
		*resume = line + 2;
		return (ft_new_token(word, OPERATOR));
	}
	if (line[i] == '<')
		word = ft_strdup("<");
	else if (line[i] == '>')
		word = ft_strdup(">");
	else
		word = ft_strdup("|");
	*resume = line + 1;
	return (ft_new_token(word, OPERATOR));
}

static bool	ft_check_single_quote_closed(char **line)
{
	(*line)++;
	while (**line != '\0' && **line != '\'')
		(*line)++;
	if (**line == '\0')
		return (false);
	else
		(*line)++;
	return (true);
}

static bool	ft_check_double_quote_closed(char **line)
{
	(*line)++;
	while (**line != '\0' && **line != '"')
		(*line)++;
	if (**line == '\0')
		return (false);
	else
		(*line)++;
	return (true);
}

int	ft_skip_word_part(char **line)
{
	while (**line != '\0' && **line != ' ' && **line != '\t' && **line != '|' && **line != '<' && **line != '>')
	{
		if (**line == '\'')
		{
			if (ft_check_single_quote_closed(line) == false)
				return (-1);
		}
		else if (**line == '"')
		{
			if (ft_check_double_quote_closed(line) == false)
				return (-2);
		}
		else
			(*line)++;
	}
	return (0);
}

char	*ft_strndup(char *s1, size_t n)
{
	size_t	s_len;
	char		*dst;

	s_len = ft_strlen(s1);
	if (n < s_len)
		s_len = n;
	dst = (char *)malloc(sizeof(char) * (s_len + 1));
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, s1, (s_len + 1));
	return (dst);
}

void	ft_tokenize_error(char *location, char **rest, char *line, int flg)
{
	printf("%s", location);
	while (*line)
		line++;
	*rest = line;
}

static t_token	*ft_add_word_token(char **resume, char *line)
{
	char	*start;
	char	*word;
	int		is_error;

	start = line;
	is_error = 0;
	is_error = ft_skip_word_part(&line);
	if (is_error == -1)
		ft_tokenize_error("Unclosed single quote", resume, line, is_error);
	if (is_error == -2)
		ft_tokenize_error("Unclosed double quote", resume, line, is_error);
	*resume = line;
	word = ft_strndup(start, *resume - start);
	return (ft_new_token(word, WORD));
}

t_token	*ft_tokenize(char *line, t_shell *shell)
{
	t_token	head;
	t_token	*token;

	shell->syntax_error = false;
	head.next = NULL;
	token = &head;
	while (*line)
	{
		if (*line == ' ' || *line == '\t')
			line++;
		else if (*line == '|' || *line == '<' || *line == '>')
		{
			token->next = ft_add_operator_token(&line, line);
			token = token->next;
		}
		else
		{
			token->next = ft_add_word_token(&line, line);
			token = token->next;
		}
	}
	token->next = ft_new_token(NULL, EOF);
	return (head.next);
}

// int main()
// {
// 	t_shell	shell;
// 	t_token *list;
// 	char *line = "a bb > cc>>>c \n ; dd&dd 222";

// 	list = ft_tokenize(line, &shell);
// 	while (list)
// 	{
// 		printf("Token: %s (Type): %d)\n", list->word, list->type);
// 		list = list->next;
// 	}
// }










# include <unistd.h>

# define COMMAND 0
# define INPUT 1
# define OUTPUT 2
# define HEREDOC 3
# define APPEND 4

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

t_node	*ft_new_node(int type, t_node *prev)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(*node));
	node->type = type;
	node->prev = prev;
	return (node);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

static bool	ft_is_same_operator(t_token *token, char *word)
{
	if (token->type != OPERATOR)
		return (false);
	return (ft_strcmp(token->word, word) == 0);
}

void	ft_parse_error(t_token **rest, t_token *token)
{
	printf("error");
	while (token && token->type != EOF)
		token = token->next;
	*rest = token;
}

bool	ft_check_near_pipe(t_node *node, t_token *token)
{
	t_token	*tmp;

	if (node->args == NULL || token->next->type == EOF)
	{
		ft_parse_error(&token, token);
		return (false);
	}
	tmp = node->args;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->type != WORD)
	{
		ft_parse_error(&token, token);
		return (false);
	}
	return (true);
}

void	ft_add_token(t_token **args, t_token *ft_new_token)
{
	if (*args == NULL)
	{
		*args = ft_new_token;
		return ;
	}
	ft_add_token(&(*args)->next, ft_new_token);
}

static void	ft_add_node(t_node **node, t_node *new_node)
{
	if (*node == NULL)
	{
		*node = new_node;
		return ;
	}
	ft_add_node(&(*node)->next, new_node);
}

t_token	*ft_clone_token(t_token *token)
{
	char	*word;

	if (token->word == NULL)
		return (ft_new_token(NULL, token->type));
	word = ft_strdup(token->word);
	if (word == NULL)
		printf("strdup");
	return (ft_new_token(word, token->type));
}

t_node	*ft_new_input_node(t_token **resume, t_token *token)
{
	t_node	*node;

	node = ft_new_node(INPUT, NULL);
	node->filename = ft_clone_token(token->next);
	node->target_fd = STDIN_FILENO;
	*resume = token->next->next;
	return (node);
}

t_node	*ft_new_output_node(t_token **resume, t_token *token)
{
	t_node	*node;

	node = ft_new_node(OUTPUT, NULL);
	node->filename = ft_clone_token(token->next);
	node->target_fd = STDOUT_FILENO;
	*resume = token->next->next;
	return (node);
}

t_node	*ft_new_heredoc_node(t_token **resume, t_token *token)
{
	t_node	*node;

	node = ft_new_node(HEREDOC, NULL);
	node->delimiter = ft_clone_token(token->next);
	node->target_fd = STDIN_FILENO;
	*resume = token->next->next;
	return (node);
}

t_node	*ft_new_append_node(t_token **resume, t_token *token)
{
	t_node	*node;

	node = ft_new_node(APPEND, NULL);
	node->filename = ft_clone_token(token->next);
	node->target_fd = STDOUT_FILENO;
	*resume = token->next->next;
	return (node);
}

void	ft_store_node_element(t_node *node, t_token **resume, t_token *token)
{
	if (token->type == WORD)
	{
		ft_add_token(&node->args, ft_clone_token(token));
		token = token->next;
	}
	else if (ft_is_same_operator(token, "<") && token->next->type == WORD)
		ft_add_node(&node->redirects, ft_new_input_node(&token, token));
	else if (ft_is_same_operator(token, ">") && token->next->type == WORD)
		ft_add_node(&node->redirects, ft_new_output_node(&token, token));
	else if (ft_is_same_operator(token, "<<") && token->next->type == WORD)
		ft_add_node(&node->redirects, ft_new_heredoc_node(&token, token));
	else if (ft_is_same_operator(token, ">>") && token->next->type == WORD)
		ft_add_node(&node->redirects, ft_new_append_node(&token, token));
	else if (token->type == EOF)
	{
		ft_add_token(&node->args, ft_clone_token(token));
		token = NULL;
	}
	else
	{
		ft_parse_error(resume, token);
		return ;
	}
	*resume = token;
}

t_node	*ft_parse(t_token *token)
{
	t_node	*head;
	t_node	*node;

	node = ft_new_node(COMMAND, NULL);
	head = node;
	while (token != NULL && token->type != EOF)
	{
		if (ft_is_same_operator(token, "|") == true)
		{
			if (ft_check_near_pipe(node, token) == false)
				return (head);
			ft_add_token(&node->args, ft_new_token(NULL, EOF));
			ft_add_node(&node->next, ft_new_node(COMMAND, node));
			node = node->next;
			token = token->next;
		}
		else
			ft_store_node_element(node, &token, token);
	}
	ft_store_node_element(node, &token, token);
	return (head);
}

int main()
{
	t_shell	shell;
	t_token *token;
	t_node  *node;
	char *line = "echo a z > b x> c | ccc >> b | cat b | e < f g | cat < i";

	token = ft_tokenize(line, &shell);
	node = ft_parse(token);
	while (node) 
	{
		printf("Node_type: %d\n", node->type);
		
		// Print arguments
		t_token *args = node->args;
		printf("Arguments: ");
		while (args) 
		{
			printf("%s ", args->word);
			args = args->next;
		}
		printf("\n");
		
		// Print redirects
		t_node *redirects = node->redirects;
		while (redirects) 
		{
			printf("Redirect_type: %d, Target_FD: %d, Filename: %s\n", redirects->type, redirects->target_fd, redirects->filename->word);
			redirects = redirects->next;
		}
		
		node = node->next;
	}
}
