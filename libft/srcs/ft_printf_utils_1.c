/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:58:22 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 18:45:21 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putunbr_len(unsigned int n, int *len)
{
	if (n >= 10)
		ft_putnbr_len(n / 10, len);
	ft_putchar_len(n % 10 + '0', len);
}
