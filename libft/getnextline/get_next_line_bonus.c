/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: string <string>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 08:03:11 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/07/03 08:33:14 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <unistd.h>

char	*ft_input_each_fd(int fd, char *input)
{
	char	*str;
	int		read_status;

	str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	read_status = 1;
	while (!ft_gnlstrchr(input, '\n') && read_status != 0)
	{
		read_status = read(fd, str, BUFFER_SIZE);
		if (read_status == -1)
		{
			free(str);
			return (NULL);
		}
		str[read_status] = '\0';
		input = ft_gnlstrjoin(input, str);
	}
	free(str);
	return (input);
}

char	*ft_getline(char *input)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!input[i])
		return (NULL);
	while (input[i] && input[i] != '\n')
		i++;
	str = (char *)ft_calloc(1, sizeof(char) * i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (input[i] && input[i] != '\n')
	{
		str[i] = input[i];
		i++;
	}
	if (input[i] == '\n')
	{
		str[i] = input[i];
		i++;
	}
	return (str);
}

char	*ft_reshape(char *input)
{
	char	*newstring;
	size_t	i;
	size_t	j;

	i = 0;
	while (input[i] && input[i] != '\n')
		i++;
	if (!input[i])
	{
		free(input);
		return (NULL);
	}
	newstring = (char *)malloc(sizeof(char) * (ft_strlen(input) - i + 1));
	if (!newstring)
		return (NULL);
	i++;
	j = 0;
	while (input[i])
		newstring[j++] = input[i++];
	newstring[j] = '\0';
	free(input);
	return (newstring);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*inputs[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	inputs[fd] = ft_input_each_fd(fd, inputs[fd]);
	if (!inputs[fd])
		return (NULL);
	line = ft_getline(inputs[fd]);
	inputs[fd] = ft_reshape(inputs[fd]);
	return (line);
}
