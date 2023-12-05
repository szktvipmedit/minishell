#include "libft.h"

char	*ft_strmapi(char *s, char (*f)(unsigned int, char))
{
  size_t	i;
	char    *str;

  if (s == NULL || f == NULL)
  return (NULL);
  str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
  if (str == NULL)
    return (NULL);
  i = 0;
  while (s[i])
  {
    str[i] = f(i, s[i]);
    i++;
  }
  str[i] = '\0';
  return (str);
}
