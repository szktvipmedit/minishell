/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generates_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:14:39 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/09/29 15:46:08 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_bonus.h"
#include "../../libft.h"

size_t	gen_c(t_format forminfo, va_list *ap)
{
	char	c;

	if (forminfo.spec == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	c = va_arg(*ap, int);
	ft_putchar_fd(c, 1);
	return (1);
}

size_t	gen_s(va_list *ap)
{
	size_t	count;
	char	*str;

	str = va_arg(*ap, char *);
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	count = ft_strlen(str);
	ft_putstr_fd(str, 1);
	return (count);
}

size_t	gen_diu(t_format forminfo, va_list *ap)
{
	size_t	print_nbr;
	int		nb;
	char	*str;

	print_nbr = 0;
	nb = va_arg(*ap, int);
	if (nb >= 0 && forminfo.plus)
		print_nbr = write(1, "+", 1);
	else if (nb >= 0 && forminfo.space)
		print_nbr = write(1, " ", 1);
	if (forminfo.spec == 'u')
		str = ft_utoa((unsigned int)nb);
	else
		str = ft_itoa(nb);
	print_nbr += ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (print_nbr);
}

size_t	gen_p(va_list *ap)
{
	size_t	print_nbr;
	size_t	p;

	p = va_arg(*ap, size_t);
	print_nbr = write(1, "0x", 2);
	if (p == 0)
	{
		write(1, "0", 1);
		return (print_nbr + 1);
	}
	recursive_hex_p(p, &print_nbr);
	return (print_nbr);
}

size_t	gen_xlx(t_format forminfo, va_list *ap)
{
	size_t			print_nbr;
	unsigned int	nb;

	nb = va_arg(*ap, unsigned int);
	print_nbr = 0;
	if (nb == 0)
		return (write(1, "0", 1));
	if (forminfo.spec == 'X')
	{
		if (forminfo.sharp)
			print_nbr = write(1, "0X", 2);
		recursive_hex_xlx(nb, forminfo, &print_nbr);
	}
	else
	{
		if (forminfo.sharp)
			print_nbr = write(1, "0x", 2);
		recursive_hex_xlx(nb, forminfo, &print_nbr);
	}
	return (print_nbr);
}
