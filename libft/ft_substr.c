#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char		*sub;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	if (s_len <= len)
		len = s_len - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	printf("ft_substr: sub %p\n", sub);
	ft_strlcpy(sub, &s[start], (len + 1));
	return (sub);
}
