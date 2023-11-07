/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexaSystem_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: string <string>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:10:56 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/07/07 06:39:58 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_bonus.h"

void	recursive_hex_p(size_t p, size_t *print_nbr)
{
	size_t	remain;
	char	c;

	if (p > 0)
	{
		remain = p % 16;
		c = HEXLOWER[remain];
		p /= 16;
		recursive_hex_p(p, print_nbr);
		write(1, &c, 1);
		*print_nbr = *print_nbr + 1;
	}
}

void	recursive_hex_xlx(unsigned int nb, t_format forminfo, size_t *print_nbr)
{
	size_t	remain;
	char	c;

	if (nb > 0)
	{
		remain = nb % 16;
		if (forminfo.spec == 'X')
			c = HEXUPPER[remain];
		else
			c = HEXLOWER[remain];
		nb /= 16;
		recursive_hex_xlx(nb, forminfo, print_nbr);
		write(1, &c, 1);
		*print_nbr = *print_nbr + 1;
	}
}
