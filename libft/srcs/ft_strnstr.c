/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:07:36 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 18:44:00 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!little[0])
		return ((char *) big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] && i + j < len)
			j++;
		if (!little[j])
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}

// int	main()
// {
// 	char str_1[] = "this is a test 123 456";
// 	char to_find_1[] = "test";

// 	char str_2[] = "Bonjourjour";
// 	char to_find_2[] = "jour";

// 	char str_3[] = "aaabcabcd";
// 	char to_find_3[] = "cd";

// 	printf("%s\n", ft_strnstr(str_1, to_find_1, 12));
// 	printf("%s\n\n", strstr(str_1, to_find_1));

// 	printf("%s\n", ft_strnstr(str_2, to_find_2, 5));
// 	printf("%s\n\n", strstr(str_2, to_find_2));
// 		printf("%s\n", ft_strnstr(str_3, to_find_3, 8));
// 	printf("%s\n\n", strstr(str_3, to_find_3));
// }
