#include "libft.h"

static size_t	ft_count_words(char *s, char c)
{
  size_t  i;
	size_t  count;

  i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static size_t	ft_word_len(char *s, char c)
{
  size_t  i;

  i = 0;
	while (s[i] && s[i] != c)
    i++;
	return (i);
}

static void ft_free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

char	**ft_split(char *s, char c)
{
  size_t  i;
	char    **strs;

	if (s == NULL)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	//printf("ft_split: strs %p\n", strs);
	if (strs == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
    while (*s && *s == c)
      s++;
		if (*s != '\0')
  		strs[i++] = ft_substr(s, 0, ft_word_len(s, c));
    if (i > 0 && strs[i - 1] == NULL)
    {
      ft_free_strs(strs);
      return (NULL);
    }
		if (*s != '\0')
    	s = s + ft_word_len(s, c);
	}
  strs[i] = NULL;
	return (strs);
}
