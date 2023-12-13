/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:25:53 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/13 18:32:43 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putptr_len(void *p, int *len)
{
	if (!p)
		(ft_putstr_len("(nil)", len));
	else
	{
		ft_putstr_len("0x", len);
		ft_puthex_len((unsigned long long)p, 0, len);
	}
}
