/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:42:02 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/09/29 14:57:55 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_bonus.h"
#include "../../libft.h"

t_format	ft_createforminfo(void)
{
	t_format	forminfo;

	forminfo.minus = 0;
	forminfo.space = 0;
	forminfo.sharp = 0;
	forminfo.spec = 0;
	forminfo.plus = 0;
	return (forminfo);
}

size_t	hub_print_nbr(t_format forminfo, va_list *ap)
{
	size_t	print_nbr;

	if (forminfo.spec == 'c')
		print_nbr = gen_c(forminfo, ap);
	if (forminfo.spec == 's')
		print_nbr = gen_s(ap);
	if (forminfo.spec == 'd' || forminfo.spec == 'i' || forminfo.spec == 'u')
		print_nbr = gen_diu(forminfo, ap);
	if (forminfo.spec == 'p')
		print_nbr = gen_p(ap);
	if (forminfo.spec == 'x' || forminfo.spec == 'X')
		print_nbr = gen_xlx(forminfo, ap);
	if (forminfo.spec == '%')
	{
		print_nbr = 1;
		ft_putchar_fd('%', 1);
	}
	return (print_nbr);
}

size_t	ft_parser(char *format, va_list *ap)
{
	t_format	forminfo;

	forminfo = ft_createforminfo();
	while (*format && !ft_strchr(SPECS, *format))
	{
		if (*format == '#')
			forminfo.sharp = 1;
		if (*format == '+')
			forminfo.plus = 1;
		if (*format == ' ')
			forminfo.space = 1;
		format++;
	}
	forminfo.spec = *format;
	return (hub_print_nbr(forminfo, ap));
}

int	invalid_format(char *format)
{
	while (*format)
	{
		if (*(format++) == '%')
		{
			if (*format == '%')
				format++;
			else if (ft_strchr(FLAGS, *(format)))
			{
				while (ft_strchr(FLAGS, *(format)))
					format++;
				if (!ft_strchr(SPECS, *(format)))
				{
					write(1, "Error", 5);
					return (1);
				}
			}
			else if (!ft_strchr(SPECS, *(format)))
			{
				write(1, "Error", 5);
				return (1);
			}
		}
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	size_t	print_nbr;
	va_list	ap;

	if (invalid_format((char *)format))
		return (0);
	print_nbr = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			if (*(++format))
				print_nbr += ft_parser((char *)format, &ap);
			while (*format && !ft_strchr(SPECS, *format))
				format++;
		}
		else
		{
			ft_putchar_fd(*format, 1);
			print_nbr++;
		}
		format++;
	}
	va_end(ap);
	return (print_nbr);
}
