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

t_token	*ft_new_token(char *word, int type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	token->word = word;
	token->type = type;
	return (token);
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
