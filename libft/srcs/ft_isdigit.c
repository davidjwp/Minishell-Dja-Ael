/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:14:43 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 18:44:00 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_isdigit(int c)

{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}

// int main(int argc, char *argv[])
// {
// 	(void) argc;
// 	printf("ft_isdigit: %d\n", ft_isdigit(argv[1][0]));
// 	printf("isdigit: %d\n", isdigit(argv[1][0]));
// 	return 0;
// }
