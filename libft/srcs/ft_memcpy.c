/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:38:09 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 18:44:00 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

// int	main()
// {
// 	char src[27] = "abcdefghijklmnopqrstuvwxyz";
// 	char dst[50] = "GeeksForGeeks is for programming geeks.";
// 	char src1[27] = "abcdefghijklmnopqrstuvwxyz";
// 	char dst1[50] = "GeeksForGeeks is for programming geeks.";
// 	printf("Before ft_memcpy(): %s\n", dst);
// 	printf("Before    memcpy(): %s\n\n", dst1);

// 	memcpy(dst, src, 26*sizeof(char));
// 	ft_memcpy(dst1, src1, 26*sizeof(char));

// 	printf("After ft_memcpy():  %s\n", dst);
// 	printf("After    memcpy():  %s\n", dst1);

// 	return 0;
// }
