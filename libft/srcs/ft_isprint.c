/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:02:10 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 18:44:00 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

// int main()
// {
// 	printf("ft_isprint: %d\n", ft_isprint('\0'));
// 	printf("isprint: %d\n", isprint('\0'));
// 	printf("ft_isprint: %d\n", ft_isprint(' '));
// 	printf("isprint: %d\n", isprint(' '));
// 	return 0;
// }
