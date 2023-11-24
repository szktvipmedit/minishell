#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	d_len;
	size_t	s_len;

	s_len = ft_strlen(src);
	if (dstsize == 0)
		return (s_len);
	d_len = ft_strlen(dst);
	if (d_len >= dstsize)
		return (dstsize + s_len);
  i = 0;
	while (i < (dstsize - d_len - 1) && src[i])
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = '\0';
	return (d_len + s_len);
}
