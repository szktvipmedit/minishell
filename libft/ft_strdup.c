#include "libft.h"

char	*ft_strdup(char *s1)
{
  size_t	s_len;
	char		*dst;

	s_len = ft_strlen(s1);
	dst = (char *)malloc(sizeof(char) * (s_len + 1));
	if (dst == NULL)
		return (NULL);
	printf("ft_strdup: new %p\n", dst);
	ft_strlcpy(dst, s1, (s_len + 1));
	return (dst);
}
