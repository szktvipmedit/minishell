#include "libft.h"

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
	printf("ft_strdnup: dst %p\n", dst);
	ft_strlcpy(dst, s1, (s_len + 1));
	return (dst);
}
