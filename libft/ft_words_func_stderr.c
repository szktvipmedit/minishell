#include "libft.h"

void	ft_putchar_count_stderr(int c, int *count)
{
	if (*count == INT_MAX || *count == -1)
	{
		*count = -1;
		return ;
	}
	write(2, &c, 1);
	(*count)++;
}

void	ft_putstr_count_stderr(char *s, int *count)
{
	size_t	i;

	i = 0;
	if (s == NULL)
	{
		ft_putstr_count_stderr("(null)", count);
		return ;
	}
	while (s[i])
	{
		ft_putchar_count_stderr(s[i], count);
		i++;
	}
}
