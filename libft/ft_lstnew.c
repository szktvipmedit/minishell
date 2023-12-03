#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	printf("lst new : %p\n", new);
	new->content = content;
	new->next = NULL;
	return (new);
}
