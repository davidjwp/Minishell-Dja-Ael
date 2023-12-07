/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:50:40 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 18:44:00 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;
	size_t	i;

	if (!n)
		return ;
	i = 0;
	ptr = s;
	while (i < n)
	{
		*(ptr + i) = '\0';
		i++;
	}
}

// int main()
// {
// 	char str[50] = "GeeksForGeeks is for programming geeks.";
// 	char str1[50] = "GeeksForGeeks is for programming geeks.";
// 	printf("Before    bzero(): %s\n", str);
// 	printf("Before ft_bzero(): %s\n\n", str1);

// // 	bzero(str, 8*sizeof(char));
// 	ft_bzero(str1, 8*sizeof(char));

// 	printf("After    bzero():  %s\n", str);
// 	printf("After ft_bzero():  %s\n", str1);

// 	return 0;
// }
