/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:19:03 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/07 18:44:00 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = -1;
	if (dst_len >= size)
		return (src_len + size);
	while (++i < size - dst_len - 1 && src[i])
		dst[dst_len + i] = (src)[i];
	dst[dst_len + i] = '\0';
	return (src_len + dst_len);
}

// int	main()
// {
// 	char dst1[] = "this is a test 123 456";
// 	char dst2[] = "this is a test 123 456";
// 	char src[] = "test";

// 	printf("Before strlcat:   %s\n", dst1);
// 	printf("Before ft_strlcat:%s\n\n", dst2);

// 	ft_strlcat(dst2, src,4);
// 	printf("After strlcat:    %s\n", strncat(dst1, src, 4));
// 	printf("After ft_strlcat: %s\n", dst2);
// }
