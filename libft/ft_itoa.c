#include "libft.h"

static size_t	ft_numlen(long nbr)
{
	size_t	i;

	i = 0;
	if (nbr <= 0)
		i++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
  size_t	len;
  long    nbr;
	char    *str;
	
	nbr = (long)n;
	len = ft_numlen(nbr);
	str = (char *)malloc(sizeof(char) * (len + 1));
	printf("ft_itoa: str %p\n", str);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
  len--;
	if (nbr == 0)
		str[0] = '0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = nbr * (-1);
	}
	while (nbr != 0)
	{
		str[len] = (nbr % 10) + '0';
		nbr = nbr / 10;
		len--;
	}
	return (str);
}
