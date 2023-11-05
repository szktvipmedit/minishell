#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && i < (n - 1)
		&& (unsigned char)s1[i] == (unsigned char)s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

#include <stdio.h>
#include <stdlib.h>

static char	*ft_strcpy(char *str, const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static size_t	ft_cnt_nbr_char(char const *s, size_t s_curr, char c)
{
	size_t	char_cnt;

	char_cnt = 0;
	while (s[s_curr] && s[s_curr] != c)
	{
		s_curr++;
		char_cnt++;
	}
	return (char_cnt);
}

static int	ft_malloc_fail(char **str, size_t sec)
{
	while (str[sec])
	{
		free(str[sec]);
		sec--;
	}
	free(str);
	return (1);
}

static int	ft_fillin(char const *s, char **str, char c)
{
	size_t	s_curr;
	size_t	sec;

	s_curr = 0;
	sec = 0;
	while (s[s_curr])
	{
		if (s[s_curr] != c)
		{
			str[sec] = malloc(sizeof(char) * (ft_cnt_nbr_char(s, s_curr, c)
						+ 1));
			if (!str[sec])
				return (ft_malloc_fail(str, sec));
			ft_strcpy(str[sec], &s[s_curr], c);
			sec++;
			s_curr = s_curr + ft_cnt_nbr_char(s, s_curr, c);
		}
		else
			s_curr++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	word_cnt;

	i = 0;
	if (!s || s[i] == '\0')
		return (NULL);
	word_cnt = 0;
	if (*s && *s != c)
		word_cnt++;
	while (s[i + 1])
	{
		if (*(s + i) == c && *(s + i + 1) != c)
			word_cnt++;
		i++;
	}
	str = malloc(sizeof(char *) * (word_cnt + 1));
	if (!str)
		return (NULL);
	if (ft_fillin(s, str, c))
		return (NULL);
	str[word_cnt] = NULL;
	return (str);
}
