/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:35:32 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 18:44:00 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char )c;
		i++;
	}
	return (s);
}

// int main()
// {
// 	char str[50] = "GeeksForGeeks is for programming geeks.";
// 	char str1[50] = "GeeksForGeeks is for programming geeks.";
// 	printf("Before    memset(): %s\n", str);
// 	printf("Before ft_memset(): %s\n\n", str1);

// // 	memset(str + 13, '.', 8*sizeof(char));
// 	ft_memset(str1 + 13, '.', 8*sizeof(char));

// 	printf("After    memset():  %s\n", str);
// 	printf("After ft_memset():  %s\n", str1);

// 	return 0;
// }
