/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 07:58:07 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/01 11:25:42 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_gnlstrchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_gnlstrjoin(char *input, char *str)
{
	char	*str_concat;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!input)
		input = ft_calloc(1, sizeof(char));
	if (!input || !str)
		return (NULL);
	str_concat = malloc(sizeof(char) * (ft_strlen(input) + ft_strlen(str) + 1));
	if (!str_concat)
		return (NULL);
	while (input[i] != '\0')
	{
		str_concat[i] = input[i];
		i++;
	}
	while (str[j] != '\0')
		str_concat[i++] = str[j++];
	str_concat[ft_strlen(input) + ft_strlen(str)] = '\0';
	free(input);
	return (str_concat);
}
