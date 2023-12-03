#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void  *ptr;

	if (count == 0 || size == 0)
		return (ft_calloc(1, 1));
	if ((SIZE_MAX / count) < size)
		return (NULL);
	ptr = (void *)malloc(size * count);
	if (ptr == NULL)
		return (NULL);
	printf("ft_calloc: new %p\n", ptr);
	ft_bzero(ptr, (size * count));
	return (ptr);
}
