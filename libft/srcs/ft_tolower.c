/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:37:24 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 18:44:00 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ' ');
	return (c);
}

// int main()
// {
// 	printf("ft_tolower: %c\n", ft_tolower('A'));
// 	printf("tolower: %c\n\n", tolower('A'));
// 	printf("ft_tolower: %c\n", ft_tolower('\\'));
// 	printf("tolower: %c\n", tolower('\\'));
// 	return 0;
// }
