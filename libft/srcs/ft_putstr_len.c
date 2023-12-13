/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <djacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 00:07:47 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/13 18:32:05 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putstr_len(char *s, int *len)
{
	int	i;

	if (!s)
		*len += write(1, "(null)", 6);
	else
	{
		i = 0;
		while (s[i])
			*len += write(1, &s[i++], 1);
	}
}
