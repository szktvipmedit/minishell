#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
  size_t  i;
	size_t	len;

	if (s1 == NULL || set == NULL)
		return (NULL);
  i = 0;
	while (s1[i] && ft_strchr(set, (int)s1[i]))
		i++;
  len = ft_strlen(s1);
  if (i == len)
		return (ft_strdup(""));
	while (len != i && ft_strchr(set, (int)s1[len]))
		len--;
	return (ft_substr(&s1[i], 0, (len - i + 1)));
}
