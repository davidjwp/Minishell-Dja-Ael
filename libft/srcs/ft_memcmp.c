/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:14:18 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 18:44:00 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((((unsigned char *)s1)[i] != ((unsigned char *)s2)[i]))
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

// int	main()
// {
// 	char str[50] = "GeeksForGeeks is for programming geeks.";
// 	char str1[50] = "GeeksForGeeks i123213";
// 	int cmp;
// 	int cmp1;

// 	printf("s1: %s\n", str);
// 	printf("s2: %s\n\n", str1);

// 	cmp = memcmp(str, str1, 16*sizeof(char));
// 	cmp1 = ft_memcmp(str, str1, 16*sizeof(char));

// 	printf("memcmp():  %d\n", cmp);
// 	printf("After ft_memcmp():  %d\n", cmp1);

// 	return 0;
// }
