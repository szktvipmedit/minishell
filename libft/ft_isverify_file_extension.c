/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isverify_file_extension.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:21:35 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/07 15:59:22 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//1:指定された拡張子
int	ft_isverify_file_extension(char *filename, char *extension)
{
	size_t	i;
	size_t	dot_i;
	size_t	len;

	if (!filename || !extension || ft_strlen(filename) == 1)
	{
		write(2, "ft_isverify_file_extension: Error\n", 34);
		exit(1);
	}
	i = 0;
	len = ft_strlen(filename);
	dot_i = len - 1;
	while (dot_i >= 0)
	{
		if (filename[dot_i] == '.')
			break ;
		dot_i--;
	}
	while (i < ft_strlen(extension))
	{
		if (dot_i == 0 || filename[dot_i++] != extension[i++])
			return (0);
	}
	return (1);
}

// int	main(void)
// {
// 	char *s = "42.fdf";
// 	printf("%i\n", ft_isverify_file_extension(s, ".fdf"));
// 	printf("%i\n", ft_isverify_file_extension("a", ".fdf"));
// 	printf("%i\n", ft_isverify_file_extension("file.txt", ".fdf"));
// 	printf("%i\n", ft_isverify_file_extension("file.fd", ".fdf"));
// 	printf("%i\n", ft_isverify_file_extension("file.df", ".fdf"));
// 	printf("%i\n", ft_isverify_file_extension("file.fdf.fdf", ".fdf"));
// 	printf("%i\n", ft_isverify_file_extension("file.fdf.excel", ".fdf"));
// 	printf("%i\n", ft_isverify_file_extension("file.fdf.excel.fdf", ".fdf"));
// }