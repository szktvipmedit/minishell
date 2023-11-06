#include "libft.h"

void	*ft_memmove(void *dst, void *src, size_t len)
{
	if (dst == NULL && src == NULL)
		return (NULL);
	if ((unsigned char *)dst < (const unsigned char *)src)
		return (ft_memcpy(dst, src, len));
  while (len > 0)
  {
    len--;
    ((unsigned char *)dst)[len] = ((const unsigned char *)src)[len];
  }
	return (dst);
}
