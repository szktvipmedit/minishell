#include "libft.h"

int	ft_memcmp(void *s1, void *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
  i = 0;
	while (i < (n - 1) && (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i]))
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
